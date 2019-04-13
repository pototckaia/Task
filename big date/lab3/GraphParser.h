#pragma once

#include <vector>
#include <string>
#include <fstream>

class GraphParser  {
 public:
	GraphParser(std::string);

	std::pair<long long, std::vector<long long>> getLine();
	bool isEnd() { return isEnd_; }

 private:
	std::ifstream file;
	bool isEnd_;
};