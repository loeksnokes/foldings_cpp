#include "graph.hpp"
#include <algorithm>

Vertex::Vertex() {
    stringsSet = std::unordered_set<std::string>();
}

void Vertex::addString(const std::string& s) {
    stringsSet.insert(s);
}

bool Vertex::containsString(const std::string& s) const {
    return stringsSet.find(s) != stringsSet.end();
}

Graph::Graph() {
    adjacencyList = std::unordered_map<Vertex*, std::vector<Vertex*>>();
    vertices = std::vector<Vertex*>();
}

void Graph::addVertex(Vertex* v) {
    vertices.push_back(v);
    adjacencyList[v] = std::vector<Vertex*>();
}

void Graph::addEdge(Vertex* src, Vertex* dst) {
    adjacencyList[src].push_back(dst);
}

void Graph::removeVertex(Vertex* v) {
    adjacencyList.erase(v);
    vertices.erase(std::remove(vertices.begin(), vertices.end(), v), vertices.end());

    for (auto& pair : adjacencyList) {
        auto& dests = pair.second;
        dests.erase(std::remove(dests.begin(), dests.end(), v), dests.end());
    }
}

std::vector<std::string> Graph::gVertStrings(Vertex* v) const {
    std::vector<std::string> keys;
    for (const auto& str : v->stringsSet) {
        keys.push_back(str);
    }
    return keys;
}