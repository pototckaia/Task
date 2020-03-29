#include <ostream>
#include <fstream>
#include <iostream>
#include <string>

#include "c_b0proj.hpp"
#include <iomanip>

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
	outFile << "Number;\tx;\ty;\tLongitude;\tLatitude;\tIntensity;\tTemperature (C);\tDistance (km);\n";
	for (std::size_t i = 0; i < slices.size(); ++i) {
		outFile
			<< std::setprecision(7)
			<< i + 1 << ";\t"
			<< slices[i].x << ";\t" << slices[i].y << ";\t"
			<< slices[i].lon << ";\t" << slices[i].lat << ";\t"
			<< slices[i].intensity << ";\t"
			<< slices[i].celsius << ";\t"
			<< slices[i].d << std::endl;
	}
}

int main(int argv, char* argc[]) {
	
	if (argv == 1) {
		return 0;
	}
	int index = 1;
	if (strcmp(argc[index], "-h") == 0) {
		std::cout
			<< "file -toXY lon lat" << std::endl
			<< "file -toLonLat x y" << std::endl
			<< "file -I[-g] x y [lon lat]" << std::endl
			<< "file -slice [-v][-f file] [-g] x1 y1 x2 y2 [lon1 lat1 lon2 lat2]" << std::endl;
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
	
	std::string type = argc[index++];
	if (type == "-toLonLat") {
		uint32_t x = std::stoi(argc[index++]);
		auto lon = proj.getLonForColumn(x);
		
		uint32_t y = std::stoi(argc[index++]);
		auto lat = proj.getLatForRow(y);
		
		std::cout
			<< "x " << x << std::endl << "y " << y  << std::endl
			<< "Lon " << lon << std::endl
			<< "Lat " << lat << std::endl;
	}
	else if (type == "-toXY") {
		auto lon = std::atof(argc[index++]);
		auto column = proj.getColumnForLon(lon);
		
		auto lat = std::atof(argc[index++]);
		auto scan = proj.getRowForLat(lat);

		std::cout
			<< "Col " << column << std::endl
			<< "Scan " << scan << std::endl;
	}
	else if (type == "-I") {
		uint32_t x, y;
		if (strcmp(argc[index], "-g") == 0) {
			++index;
			auto lon = std::atof(argc[index++]);
			auto lat = std::atof(argc[index++]);
			x = proj.getColumnForLon(lon);
			y = proj.getRowForLat(lat);
		} 
		else {
			x = std::stoi(argc[index++]);
			y = std::stoi(argc[index++]);
		}
		std::cout
			<< "raw " << proj.getRawOfPixel(x, y) << std::endl;
	}
	else if (type == "-slice") {
		std::string outFileName = "line.csv";
		bool saveVector = false;
		if (strcmp(argc[index], "-v") == 0) {
			outFileName = "line.vec";
			++index;
			saveVector = true;
		}
		if (strcmp(argc[index], "-f") == 0) {
			++index;
			outFileName = argc[index++];
		}

		std::vector<GeoSlicePiece> slices;
		if (strcmp(argc[index], "-g") == 0) {
			++index;
			auto lon1 = std::atof(argc[index++]);
			auto lat1 = std::atof(argc[index++]);
			auto lon2 = std::atof(argc[index++]);
			auto lat2 = std::atof(argc[index++]);
			slices = proj.getSlice(lon1, lat1, lon2, lat2);
		}
		else {
			uint32_t x1 = std::stoi(argc[index++]);
			uint32_t y1 = std::stoi(argc[index++]);
			uint32_t x2 = std::stoi(argc[index++]);
			uint32_t y2 = std::stoi(argc[index++]);
			slices = proj.getSlice(x1, y1, x2, y2);
		}
		if (saveVector) {
			exportSliceToVec(outFileName, slices);
		}
		else {
			exportSliceToSvn(outFileName, slices);
		}
	}

}
