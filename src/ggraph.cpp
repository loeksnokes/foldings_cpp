#include "ggraph.hpp"

GGraph::GGraph() {
    adjacencyList = std::unordered_map<Graph*, std::vector<Graph*>>();
    vertices = std::vector<Graph*>();
}

void GGraph::addVertex(Graph* v) {
    vertices.push_back(v);
    adjacencyList[v] = std::vector<Graph*>();
}

void GGraph::addEdge(Graph* src, Graph* dst) {
    adjacencyList[src].push_back(dst);
}

void GGraph::removeVertex(Graph* v) {
    adjacencyList.erase(v);
    vertices.erase(std::remove(vertices.begin(), vertices.end(), v), vertices.end());

    for (auto& pair : adjacencyList) {
        auto& dests = pair.second;
        dests.erase(std::remove(dests.begin(), dests.end(), v), dests.end());
    }
}