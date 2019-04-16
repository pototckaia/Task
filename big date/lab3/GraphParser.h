#pragma once

#include <vector>
#include <string>
#include <fstream>

struct nodeGraph {
	long long id;
	std::vector<long long> friends;
	bool isUsed = false;
};


class GraphParser  {
 public:
	GraphParser(std::string);

	nodeGraph getLine();
	bool isEnd() { return isEnd_; }

 private:
	std::ifstream file;
	bool isEnd_;
};