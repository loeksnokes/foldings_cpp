#include "graph.hpp"

#include <algorithm>

Vertex::Vertex() {}

void Vertex::addString(const std::string& s) {
    stringsSet.insert(s);
}

bool Vertex::containsString(const std::string& s) const {
    return stringsSet.count(s) > 0;
}

bool Vertex::operator<(const Vertex& other) const {
    // Compare based on the smallest string in each set
    if (stringsSet.empty() && other.stringsSet.empty()) {
        return false; // Both are empty, so they are equal
    }
    if (stringsSet.empty()) {
        return true; // This vertex is empty, the other is not, so this is smaller
    }
    if (other.stringsSet.empty()) {
        return false; // Other vertex is empty, this is not, so this is larger
    }

    auto it1 = stringsSet.begin();
    auto it2 = other.stringsSet.begin();
    return *it1 < *it2;
}

bool Vertex::operator==(const Vertex& other) const {
    return stringsSet == other.stringsSet;
}

Graph::Graph(int k, int n) : kmerLength(k), alphabetSize(n) {}

void Graph::addVertex(std::shared_ptr<Vertex> v) {
    vertices.insert(v);
}

void Graph::addEdge(std::shared_ptr<Vertex> v1, std::shared_ptr<Vertex> v2) {
    adjacencyList[v1].push_back(v2);
}

bool Graph::areAdjacent(const std::shared_ptr<Vertex> v1, const std::shared_ptr<Vertex> v2) const {
    auto it = adjacencyList.find(v1);
    if (it != adjacencyList.end()) {
        const auto& neighbors = it->second;
        for (const auto& neighbor : neighbors) {
            if (neighbor == v2) {
                return true;
            }
        }
    }
    return false;
}

bool Graph::containsVertex(const std::shared_ptr<Vertex> v) const {
    return vertices.find(v) != vertices.end();
}

const std::vector<std::shared_ptr<Vertex>>& Graph::getNeighbors(const std::shared_ptr<Vertex> v) const {
    auto it = adjacencyList.find(v);
    if (it != adjacencyList.end()) {
        return it->second;
    } else {
        // Return an empty vector if the vertex is not in the adjacency list
        static const std::vector<std::shared_ptr<Vertex>> emptyVector;
        return emptyVector;
    }
}

void Vertex::roll(int symbol, std::set<std::string>& rolledKmers) const {
    if (symbol < 0 || symbol > 9) {
        return;
    }
    char c = '0' + symbol;
     for (const auto& kmer : stringsSet) {
            std::string newKmer = kmer.substr(1) + c; // Roll the k-mer
            rolledKmers.insert(newKmer);
        }
}

std::set<std::string> Vertex::getKmers() const {
    return stringsSet;
}