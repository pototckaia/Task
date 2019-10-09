#include <iostream>
#include <map>
#include <algorithm>
#include "GraphParser.h"

using Graph = std::vector<nodeGraph>;
using ToIndex = std::map<long long, std::size_t>;

void dfs(long long id, Graph& graph, ToIndex& toIndex) {
	auto index = toIndex[id];
	graph[index].isUsed = true;
	for (auto e: graph[index].friends) {
		if (toIndex.count(e) && !graph[toIndex[e]].isUsed) {
			dfs(graph[toIndex[e]].id, graph, toIndex);
		}
	}
}


int main() {
	GraphParser p("graph.txt");

	Graph graph;
	ToIndex  toIndex;

	while (!p.isEnd()) {
		graph.push_back(p.getLine());
		auto idParent = graph.back().id;
		auto& parentFriends = graph.back().friends;
		toIndex.emplace(idParent, graph.size() - 1);
	}

	long long count_comp = 0;
	for (auto& e: graph) {
		if (!e.isUsed){
			++count_comp;
			dfs(e.id, graph, toIndex);
		}
	}

	std::cout << "Компонент связности: "
			  << count_comp << std::endl;

}