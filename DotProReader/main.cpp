#include <ostream>
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <random>

#include "c_b0proj.hpp"
#include <numeric>

void exportSliceToVec(std::string name, const std::vector<GeoSlicePiece>& slices) {
	std::ofstream writer(name);
	for (auto p : slices) {
		writer 
			<< "TYPE = POINT COLOR = 10 GEO = ("
			<< p.lon << ", " << p.lat <<
			") WIDTH = 3 IS_WIDTH_ADAPTIVE = FALSE" << std::endl;
	}
}

void exportSliceToSvn(std::string name, const std::vector<GeoSlicePiece>& slices) {
	std::ofstream outFile(name);
	outFile << "Number;x;y;Longitude;Latitude;Intensity;Temperature (C);Distance (km);" << std::endl;
	for (std::size_t i = 0; i < slices.size(); ++i) {
		outFile
			<< std::setprecision(7)
			<< i + 1 << ";"
			<< slices[i].x << ";" << slices[i].y << ";"
			<< slices[i].lon << ";" << slices[i].lat << ";"
			<< slices[i].intensity << ";"
			<< slices[i].celsius << ";"
			<< slices[i].d << std::endl;
	}
}

int main(int argv, char* argc[]) {

	if (argv == 1) {
		return 0;
	}
	int index = 1;
	if (strcmp(argc[index], "-h") == 0) {
		std::ifstream file("api.txt");
		std::string str;
		while (std::getline(file, str)) {
			std::cout << str << std::endl;
		}
		return 0;
	}

	auto fileName = argc[index++];
	std::ios_base::sync_with_stdio(false);
	std::ifstream reader(fileName, std::ios::in | std::ios::binary);
	reader.seekg(0, std::ios::beg);
	if (!reader.is_open()) {
		return 0;
	}
	Projection proj;
	proj.read(reader);
	proj.printf();
	
	if (index > argv)
		return 0;

	std::string type = argc[index++];
	if (type == "-toLonLat" && index + 2 <= argv) {
		uint32_t x = std::stoi(argc[index++]);
		auto lon = proj.getLonForColumn(x);
		
		uint32_t y = std::stoi(argc[index++]);
		auto lat = proj.getLatForRow(y);
		
		std::cout
			<< "x " << x << std::endl << "y " << y  << std::endl
			<< "Lon " << lon << std::endl
			<< "Lat " << lat << std::endl;
	}
	else if (type == "-toXY" && index + 2 <= argv) {
		auto lon = std::atof(argc[index++]);
		auto column = proj.getColumnForLon(lon);
		
		auto lat = std::atof(argc[index++]);
		auto scan = proj.getRowForLat(lat);

		std::cout
			<< "Col " << column << std::endl
			<< "Scan " << scan << std::endl;
	}
	else if (type == "-I") {
		uint32_t x = 0, y = 0;
		if (strcmp(argc[index], "-g") == 0 && index + 3 <= argv) {
			++index;
			auto lon = std::atof(argc[index++]);
			auto lat = std::atof(argc[index++]);
			x = proj.getColumnForLon(lon);
			y = proj.getRowForLat(lat);
			std::cout << "raw " << proj.getRawOfPixel(x, y) << std::endl;

		} 
		else if (index + 2 <= argv) {
			x = std::stoi(argc[index++]);
			y = std::stoi(argc[index++]);
			std::cout << "raw " << proj.getRawOfPixel(x, y) << std::endl;
		}
	}
	else if (type == "-slice") {
		std::string outFileName = "line.csv";
		bool saveVector = false;
		if (index <= argv && strcmp(argc[index], "-v") == 0) {
			outFileName = "line.vec";
			++index;
			saveVector = true;
		}
		if (index + 1 <= argv && strcmp(argc[index], "-f") == 0) {
			++index;
			outFileName = argc[index++];
		}

		int n = -1;
		bool isStd = true;
		if (index <= argv && strcmp(argc[index], "-normal") == 0) {
			++index;
			if (index <= argv && strcmp(argc[index], "-med") == 0) {
				++index;
				isStd = false;
			}
			else if (index <= argv && strcmp(argc[index], "-std") == 0) {
				++index;
			}
			if (index + 1 <= argv && strcmp(argc[index], "-n") == 0) {
				++index;
				n = std::stoi(argc[index++]);
			}
		}

		std::vector<GeoSlicePiece> slices;
		if (index + 4 <= argv && strcmp(argc[index], "-g") == 0) {
			++index;
			auto lon1 = std::atof(argc[index++]);
			auto lat1 = std::atof(argc[index++]);
			auto lon2 = std::atof(argc[index++]);
			auto lat2 = std::atof(argc[index++]);
			slices = proj.getSlice(lon1, lat1, lon2, lat2);
		}
		else if (index + 4 <= argv) {
			uint32_t x1 = std::stoi(argc[index++]);
			uint32_t y1 = std::stoi(argc[index++]);
			uint32_t x2 = std::stoi(argc[index++]);
			uint32_t y2 = std::stoi(argc[index++]);
			slices = proj.getSlice(x1, y1, x2, y2);
		}
		
		if (n > 0) {
			for (auto slice : slices) {
				auto normal = proj.getNormal(slices, slice.x, slice.y, n);
				std::vector<int> intensities;
				std::vector<int> celsiuses;
				for (auto [x, y] : normal) {
					intensities.emplace_back(proj.getRawOfPixel(x, y));
					celsiuses.emplace_back(proj.getGetOfPixel(x, y));
				}
				
				if (isStd) {
					slice.intensity = std::ceil(std::accumulate(intensities.begin(), intensities.end(), 0) / intensities.size());
					slice.celsius = std::accumulate(celsiuses.begin(), celsiuses.end(), 0) / celsiuses.size();
				}
				else {
					auto median_it = intensities.begin() + intensities.size() / 2;
					std::nth_element(intensities.begin(), median_it, intensities.end());
					slice.intensity = *median_it;
					
					median_it = celsiuses.begin() + celsiuses.size() / 2;
					std::nth_element(celsiuses.begin(), median_it, celsiuses.end());
					slice.celsius = *median_it;
				}
			}
		}


		if (saveVector) {
			exportSliceToVec(outFileName, slices);
		}
		else {
			exportSliceToSvn(outFileName, slices);
		}
	}
}
