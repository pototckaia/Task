/*-------------------------------------------------------------------------
    c_b0proj.hpp
-------------------------------------------------------------------------*/
#pragma once

#include <vector>
#include <ostream>
#include <fstream>
#include <iostream>
#include <functional>
#include <algorithm>

const double PI = 3.14159265358979323846;

enum ProjType { mrt = 1, eqd, none };

inline ProjType getProjType(uint16_t v) {
	switch (v) {
	case 1: return ProjType::mrt;
	case 2: return ProjType::eqd;
	default: return ProjType::none;
	}
}

inline double toDeg(double rad) {
	return rad * (180.f / PI);
}

inline double toRad(double grad) {
	return grad * (PI / 180.f);
}

struct GeoData {
	unsigned char   formatType;
	char    satName[13];
	uint32_t   satId;
	uint32_t   revNum;
	uint16_t  year;
	uint16_t  day;
	uint32_t   dayTime;

	ProjType projType;

	uint16_t  rowsNum; //height
	uint16_t  columnsNum;//width

	float   latLeftDown;
	float   lonLeftDown;
	float   latSize;
	float   lonSize;
	float   latRes;
	float   lonRes;
	
	double  ka;
	double  kb;
	
	std::vector<int16_t> raw;
};

struct GeoSlicePiece {
	std::size_t i;
	double d;
	uint32_t x, y;
	double lon, lat;
	int32_t intensity, celsius;
};

struct Projection {
    GeoData b0;   
	double   realLatRes;
	double   realLonRes;
	const double r = 6371.0;

	using slice = std::vector<GeoSlicePiece>;

	void read(std::ifstream& reader) {
		reader.read(reinterpret_cast<char*>(&b0.formatType), sizeof(b0.formatType));
		reader.read(b0.satName, 13 * sizeof(char));
		reader.read(reinterpret_cast<char*>(&b0.satId), sizeof(b0.satId));
		reader.read(reinterpret_cast<char*>(&b0.revNum), sizeof(b0.revNum));
		reader.read(reinterpret_cast<char*>(&b0.year), sizeof(b0.year));
		reader.read(reinterpret_cast<char*>(&b0.day), sizeof(b0.day));
		reader.read(reinterpret_cast<char*>(&b0.dayTime), sizeof(b0.dayTime));

		char spare[42];
		reader.read(spare, 42 * sizeof(char));

		uint16_t  type;
		reader.read(reinterpret_cast<char*>(&type), sizeof(type));
		b0.projType = getProjType(type);
		reader.read(reinterpret_cast<char*>(&b0.rowsNum), sizeof(b0.rowsNum));
		reader.read(reinterpret_cast<char*>(&b0.columnsNum), sizeof(b0.columnsNum));
		reader.read(reinterpret_cast<char*>(&b0.latLeftDown), sizeof(b0.latLeftDown));
		reader.read(reinterpret_cast<char*>(&b0.lonLeftDown), sizeof(b0.lonLeftDown));
		reader.read(reinterpret_cast<char*>(&b0.latSize), sizeof(b0.latSize));
		reader.read(reinterpret_cast<char*>(&b0.lonSize), sizeof(b0.lonSize));
		reader.read(reinterpret_cast<char*>(&b0.latRes), sizeof(b0.latRes));
		reader.read(reinterpret_cast<char*>(&b0.lonRes), sizeof(b0.lonRes));
		reader.read(reinterpret_cast<char*>(&b0.ka), sizeof(b0.ka));
		reader.read(reinterpret_cast<char*>(&b0.kb), sizeof(b0.kb));
		realLonRes = b0.lonSize / (b0.columnsNum - 1);
		realLatRes = b0.latSize / (b0.rowsNum - 1);
		if (getProjType(b0.projType) == ProjType::mrt) {
			double min_lat = mercatorLat(b0.latLeftDown);
			double max_lat = mercatorLat(b0.latLeftDown + b0.latSize);
			realLatRes = (max_lat - min_lat) / (b0.rowsNum - 1);
		}

		reader.seekg(512, 0);
		b0.raw.resize(b0.rowsNum * b0.columnsNum);
		for (std::size_t i = 0; i < b0.raw.size(); ++i) {
			uint16_t value;
			reader.read(reinterpret_cast<char*>(&value), sizeof(value));
			b0.raw[i] = value;
		}
	}

	void printf() const {
		std::cout
			<< "Type format FFh1: '" << b0.formatType << "'" << std::endl
			<< "Name IS3: " << b0.satName << std::endl
			<< "Id IS3: " << b0.satId << std::endl
			<< "Coil number: " << b0.revNum << std::endl
			<< "Year: " << b0.year << std::endl
			<< "Day: " << b0.day << std::endl
			<< "Mili: " << b0.dayTime << std::endl;

		std::string nameProjection = "";
		switch (b0.projType) {
		case ProjType::mrt: nameProjection = "Mercator"; break;
		case ProjType::eqd: nameProjection = "Equidistant"; break;
		default: nameProjection = "unknown"; break;
		}

		std::cout
			<< "Type projection: " << nameProjection << std::endl
			<< "Number of lines: " << b0.rowsNum << std::endl
			<< "Number of pixels in a row: " << b0.columnsNum << std::endl
			<< "Latitude: " << b0.latLeftDown << std::endl
			<< "Longitude: " << b0.lonLeftDown << std::endl
			<< "Size of latitude: " << b0.latSize << std::endl
			<< "Size of longitude: " << b0.lonSize << std::endl
			<< "Step of latitude: " << b0.latRes << std::endl
			<< "Step of longitude: " << b0.lonRes << std::endl;
	}

private:
	double mercatorLat(double lat) const {
		lat = lat * atan2(1, 1) / 90;
		double mLat = log(tan(0.5 * lat + atan2(1, 1)));
		mLat = 90 * mLat / atan2(1, 1);
		return mLat;
	}

public:

	int32_t getRawOfPixel(uint32_t x, uint32_t y) {
		return b0.raw[(x + (b0.columnsNum * (b0.rowsNum - y - 1)))];
	}

	int32_t getGeoOfPixel(uint32_t x, uint32_t y) {
		auto value = getRawOfPixel(x, y);
		auto geo = value * b0.ka + b0.kb;
		return value < 0 ? -999 : std::floor(geo);
	}

	double getLonForColumn(uint32_t x) const {
		return b0.lonLeftDown + x * realLonRes; // (x + 0.5) * self.info.real_step_lon
	}

	double getLatForRow(uint32_t y) const {
		//y = b0.rowsNum - y;
		//if (b0.projType == ProjType::mrt) {
		//	auto min_lat = mercatorLat(b0.latLeftDown);
		//	auto lat = min_lat + y * realLatRes;
		//	lat = lat * atan2(1, 1) / 90;
		//	double mlat = 2.0 * (atan(exp(lat)) - atan2(1, 1));
		//	lat = 90 * mlat / atan2(1, 1);
		//	return mlat;
		//}
		//return b0.latLeftDown + y * realLatRes;
		double width = (b0.columnsNum / b0.lonSize * 360) / (2 * PI);
		double map_offset = width * log(tan((PI / 4) + (toRad(b0.latLeftDown) / 2)));
		double a = (b0.rowsNum + map_offset - y - 0.52) / width;
		return 180 / PI * (2 * atan(exp(a)) - PI / 2);
	}

	uint32_t getColumnForLon(double lon) const {
		auto x = std::floor((lon - b0.lonLeftDown) / realLonRes);
		return x;
	}

	uint32_t getRowForLat(double lat) const {
		//if (b0.projType == ProjType::mrt) {
		//	lat = mercatorLat(lat);
		//	auto min_lat = mercatorLat(b0.latLeftDown);
		//	auto y = (lat - min_lat) / realLatRes;
		//	auto rounded_y = std::ceil(b0.rowsNum - y - 0.5);
		//	return rounded_y;
		//}
		double width = (b0.columnsNum / b0.lonSize * 360) / (2 * PI);
		double map_offset = width * log(tan((PI / 4) + (toRad(b0.latLeftDown) / 2)));
		double y = b0.rowsNum - ((width * log(tan((PI / 4) + (toRad(lat) / 2)))) - map_offset) - 0.5;
		return floor(y);
	}

	double getDirection(double lon1, double lat1, double lon2, double lat2) {
		auto lonARad = toRad(lon1);
		auto lonBRad = toRad(lon2);
		auto latARad = toRad(lat1);
		auto latBRad = toRad(lat2);
		return  r * acos(sin(latARad) * sin(latBRad) + cos(latARad) * cos(latBRad) * cos(lonARad - lonBRad)	);
	}

	std::vector<GeoSlicePiece> getSlice(uint32_t startX, uint32_t startY, uint32_t endX, uint32_t endY) {
		auto line = getLine(startX, startY, endX, endY);

		std::vector<GeoSlicePiece> slice(line.size());
		for (std::size_t i = 0; i < line.size(); ++i) {
			slice[i].x = line[i].first; slice[i].y = line[i].second;
			slice[i].lon = getLonForColumn(line[i].first); slice[i].lat = getLatForRow(line[i].second);
			slice[i].d = getDirection(slice[i].lon, slice[i].lat,
				getLonForColumn(line[0].first), getLatForRow(line[0].second));
			slice[i].intensity = getRawOfPixel(slice[i].x, slice[i].y);
			slice[i].celsius = getGeoOfPixel(slice[i].x, slice[i].y);
		}
		return slice;
	}

	std::vector<GeoSlicePiece> getSlice(double lon1, double lat1, double lon2, double lat2) {
		auto line = getLine(lon1, lat1, lon2, lat2);

		std::vector<GeoSlicePiece> slice(line.size());
		for (std::size_t i = 0; i < line.size(); ++i) {
			slice[i].lon = line[i].first; slice[i].lat = line[i].second;
			slice[i].x = getColumnForLon(line[i].first); slice[i].y = getRowForLat(line[i].second);
			slice[i].d = getDirection(
				slice[i].lon, slice[i].lat,
				line[0].first, line[0].second);
			slice[i].intensity = getRawOfPixel(slice[i].x, slice[i].y);
			slice[i].celsius = getGeoOfPixel(slice[i].x, slice[i].y);
		}
		return slice;
	}
	
	std::vector<std::pair<uint32_t, uint32_t>> getLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) {
		std::vector<std::pair<uint32_t, uint32_t>> result;
		int dy = y2 - y1;
		int dx = x1 - x2;
		int signX = dx < 0 ? -1 : 1;
		int signY = dy < 0 ? -1 : 1;
		auto x = x1;
		auto y = y1;
		int f = 0;
		if (abs(dy) < abs(dx)) {
			do {
				f += dy * signY;
				if (f > 0) {
					f -= dx * signX;
					y += signY;
				}
				x -= signX;
				result.emplace_back(x, y);
			} while (x != x2 || y != y2);
		}
		else {
			do {
				f += dx * signX;
				if (f > 0) {
					f -= dy * signY;
					x -= signX;
				}
				y += signY;
				result.emplace_back(x, y);
			} while (x != x2 || y != y2);
		}
		return result;
	}

	std::vector<std::pair<double, double>> getLine(double lon1, double lat1, double lon2, double lat2) {
		auto x1 = getColumnForLon(lon1);
		auto y1 = getRowForLat(lat1);
		auto x2 = getColumnForLon(lon2);
		auto y2 = getRowForLat(lat2);
		auto n = std::max(fabs(int(x1) - int(x2)), fabs(int(y1) - int(y2)));
		double dlon = (lon2 - lon1) / n;
		double dlat = (lat2 - lat1) / n;
			
		double lon = lon1, lat = lat1;
		std::vector<std::pair<double, double>> result;
		for (std::size_t i = 0; i < n; ++i) {
			result.emplace_back(lon, lat);
			lon += dlon; lat += dlat;
		}
		return result;
	}

	std::vector<std::pair<uint32_t, uint32_t>> getNormal(slice& s, uint32_t x0, uint32_t y0, int offset) {
		std::vector<std::pair<uint32_t, uint32_t>> result;
		result.emplace_back(x0, y0);

		auto k1 = (int(s.back().y) - int(s.front().y)) / (int(s.back().x) - int(s.front().y));
		auto b2 = int(y0) + 1 / k1 * int(x0);
		for (int i = -offset; i <= offset; ++i) {
			int xn = x0 + i;
			int yn = std::ceil((-1 / k1) * xn + b2);
			if (xn >= 0 && xn < b0.columnsNum && yn >= 0 && yn < b0.rowsNum) {
				result.emplace_back(uint32_t(xn), uint32_t(yn));
			}
		}
		return  result;
	}
};
