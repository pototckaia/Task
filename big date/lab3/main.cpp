#include <iostream>
#include "GraphParser.h"

int main() {

	GraphParser p("graph_small.txt");

	while (!p.isEnd()) {
		auto t = p.getLine();
		std::cout << t.first << ": ";
		for (auto& e: t.second) {
			std::cout << e << " ";
		}
		std::cout << std::endl;
	}
}