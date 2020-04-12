#include <ostream>
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <random>
#include <numeric>

#include "c_b0proj.hpp"
#include "cxxopts.hpp"

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

int main(int args, char* argv[]) {
	cxxopts::Options options(argv[0]);

	std::string proFileName, sliceFileName = "slice";
	uint32_t normalN;
	using lonLatType = std::vector<double>;
	using rowColType = std::vector<uint32_t>;
	std::vector<double> lonLatVec;
	std::vector<uint32_t> rowColVec;

	const std::string toXY = "toXY";
	const std::string toLonLat = "toLonLat";
	const std::string Ill = "Ill";
	const std::string Ixy = "Ixy";
	const std::string sliceLL = "sliceLL";
	const std::string sliceXY = "sliceXY";

	options
		.add_options()
		("h, help", "Print help")
		("f, file", "Path to file *.pro", cxxopts::value<std::string>(proFileName))
		("p, print", "Print info pro file")
		(toXY, "Translation latitude and longitude to row and column", cxxopts::value<lonLatType>(lonLatVec))
		(toLonLat, "Translation row and column to latitude and longitude", cxxopts::value<rowColType>(rowColVec))
		(Ill, "Get intensity from latitude and longitude", cxxopts::value<lonLatType>(lonLatVec))
		(Ixy, "Get intensity from row and column", cxxopts::value<rowColType>(rowColVec))

		(sliceLL, "Get slice from <lon1> <lat1> <lon2> <lat2>", cxxopts::value<lonLatType>(lonLatVec))
		(sliceXY, "Get slice from <x1> <y1> <x2> <y2>", cxxopts::value<rowColType>(rowColVec))
		("sliceFile", "Name file where safe slice", cxxopts::value<std::string>(sliceFileName))
		("sliceV", "Safe vector file slice")
		("std", "Take the average in the perpendicular to the point in the slice")
		("med", "Take the median in the perpendicular to the point in the slice")
		("n", "Number of pixel for normal to slice", cxxopts::value<uint32_t>(normalN));
	options.parse_positional({ "std", "n"});
	options.parse_positional({ "med", "n"});

	
	try {
		auto result = options.parse(args, argv);

		if (result.count("help")) {
			std::cout << options.help() << std::endl;
			return 0;
		}

		if (proFileName.empty()) {
			std::cout << "Error command argument: Not specify a *.pro fileName";
			return 0;
		}

		if ((result.count(toLonLat) || result.count(Ixy)) && rowColVec.size() != 2) {
			std::cout << "Error command argument: Need <lon> <lat>" << std::endl;
			return 0;
		}

		if ((result.count(toXY) || result.count(Ill)) && lonLatVec.size() != 2) {
			std::cout << "Error command argument: Need <x> <y>" << std::endl;
			return 0;
		}

		if (result.count(sliceLL) && lonLatVec.size() != 4) {
			std::cout << "Error command argument: Need <lon1> <lat1> <lon2> <lat2>" << std::endl;
			return 0;
		}

		if (result.count(sliceXY) && rowColVec.size() != 4) {
			std::cout << "Error command argument: Need <x1> <y1> <x2> <y2>" << std::endl;
			return 0;
		}

		std::ios_base::sync_with_stdio(false);
		std::ifstream reader(proFileName, std::ios::in | std::ios::binary);
		reader.seekg(0, std::ios::beg);
		if (!reader.is_open()) {
			std::cout << "Error: Can't open file: " << proFileName;
			return 0;
		}

		Projection proj;
		proj.read(reader);

		if (result.count("p")) {
			proj.printf();
		}
		
		if (result.count(toXY)) {
			auto column = proj.getColumnForLon(lonLatVec[0]);
			auto scan = proj.getRowForLat(lonLatVec[1]);

			std::cout
				<< "Translation lon, lat: " << lonLatVec[0] << " " << lonLatVec[1] << std::endl
				<< "Col " << column << std::endl
				<< "Scan " << scan << std::endl;
			return 0;
		}

		if (result.count(toLonLat)) {
			auto lon = proj.getLonForColumn(rowColVec[0]);
			auto lat = proj.getLatForRow(rowColVec[1]);
			std::cout
				<< "Translation x, y: " << rowColVec[0] << " " << rowColVec[1] << std::endl
				<< "Lon " << lon << std::endl
				<< "Lat " << lat << std::endl;
			return 0;
		}

		if (result.count(Ill) || result.count(Ixy)) {
			uint32_t x = 0, y = 0;
			if (result.count(Ill)) {
				x = proj.getColumnForLon(lonLatVec[0]);
				y = proj.getRowForLat(lonLatVec[1]);
			}
			else {
				x = rowColVec[0];
				y = rowColVec[1];
			}
			std::cout << "Intensity:" << proj.getRawOfPixel(x, y) << std::endl;
			return 0;
		}

		if (result.count(sliceLL) || result.count(sliceXY)) {
			std::vector<GeoSlicePiece> slices;
			if (result.count(sliceLL)) {
				slices = proj.getSlice(lonLatVec[0], lonLatVec[1], lonLatVec[2], lonLatVec[3]);
			}
			else {
				slices = proj.getSlice(rowColVec[0], rowColVec[1], rowColVec[2], rowColVec[3]);
			}

			if (result.count("normalStd") || result.count("normalMed")) {
				bool isStd = result.count("normalStd");
				for (auto slice : slices) {
					auto normal = proj.getNormal(slices, slice.x, slice.y, normalN);
					std::vector<int32_t> intensities, celsiuses;
					for (auto normalPair : normal) {
						auto x = normalPair.first;
						auto y = normalPair.second;
						intensities.emplace_back(proj.getRawOfPixel(x, y));
						celsiuses.emplace_back(proj.getGeoOfPixel(x, y));
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
			
			bool saveVector = result.count("sliceV");
			if (result.count("sliceFile")) {
				auto typeFile = std::find_if(sliceFileName.rbegin(), sliceFileName.rend(),
					[](int ch) { return ch == '.'; }
				);
				sliceFileName.erase(typeFile.base() - 1, sliceFileName.end());
			}

			exportSliceToSvn(sliceFileName + ".csv", slices);
			if (saveVector) {
				exportSliceToVec(sliceFileName + ".vec", slices);
			}

			return 0;
		}

	}
	catch (const cxxopts::OptionException & e) {
		std::cout << "Error command argument: " << e.what() << std::endl;
		return 0;
	}
}