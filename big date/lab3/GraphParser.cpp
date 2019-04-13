#include "GraphParser.h"

GraphParser::GraphParser(std::string filename)
	: file(filename), isEnd_(false) {}

std::pair<long long, std::vector<long long>> GraphParser::getLine() {
	long long id;
	std::vector<long long> friends;
	if (isEnd_) {
		return std::make_pair(id, friends);
	}
	file >> id;
	if (file.peek() != ':') {
		throw std::logic_error("Parse error");
	}
	file.get();
	while(file.peek() == ' ' || file.peek() == ',') {
		file.get(); //
		long long tmp;
		file >> tmp;
		friends.push_back(tmp);
	}
	while (std::isspace(file.peek())) { file.get(); }
	isEnd_ = file.eof();
	return std::make_pair(id, friends);
}