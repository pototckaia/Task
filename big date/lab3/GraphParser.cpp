#include "GraphParser.h"

GraphParser::GraphParser(std::string filename)
	: file(filename), isEnd_(false) {}

nodeGraph GraphParser::getLine() {
	nodeGraph node;
	if (isEnd_) {
		return node;
	}
	file >> node.id;
	if (file.peek() != ':') {
		throw std::logic_error("Parse error");
	}
	file.get();
	while(file.peek() == ' ' || file.peek() == ',') {
		file.get(); //
		long long tmp;
		file >> tmp;
		node.friends.push_back(tmp);
	}
	while (std::isspace(file.peek())) { file.get(); }
	isEnd_ = file.eof();
	return node;
}