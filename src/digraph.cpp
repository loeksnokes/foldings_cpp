#include "digraph.hpp"

void Digraph::addVertex(int v) {
    vertices.push_back(v);
    adjacencyList[v] = std::vector<int>();
}

void Digraph::addEdge(int src, int dst) {
    adjacencyList[src].push_back(dst);
}

bool Digraph::IsDigraphIsomorphic(Digraph* g2) {
    if (vertices.size() != g2->vertices.size()) {
        return false;
    }

    std::unordered_map<int, bool> used;
    std::unordered_map<int, int> mapping;

    return tryIsomorphism(vertices[0], g2->vertices, used, mapping, g2);
}

bool Digraph::tryIsomorphism(int v1, std::vector<int>& vertices2, std::unordered_map<int, bool>& used, std::unordered_map<int, int>& mapping, Digraph* g2) {
    if (mapping.size() == vertices.size()) {
        return true;
    }

    for (int v2 : vertices2) {
        if (used[v2]) {
            continue;
        }

        mapping[v1] = v2;
        used[v2] = true;

        if (checkConsistency(v1, v2, mapping, g2)) {
            int nextVertex = nextUnmappedVertex(mapping);
            if (tryIsomorphism(nextVertex, vertices2, used, mapping, g2)) {
                return true;
            }
        }

        mapping.erase(v1);
        used[v2] = false;
    }

    return false;
}

bool Digraph::checkConsistency(int v1, int v2, std::unordered_map<int, int>& mapping, Digraph* g2) {
    auto neighbors1 = adjacencyList[v1];
    auto neighbors2 = g2->adjacencyList[v2];

    if (neighbors1.size() != neighbors2.size()) {
        return false;
    }

    for (int n1 : neighbors1) {
        auto mappedNeighbor = mapping[n1];
        if (mapping.count(n1)) {
            bool found = false;
            for (int n2 : neighbors2) {
                if (mappedNeighbor == n2) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                return false;
            }
        }
    }

    return true;
}

int Digraph::nextUnmappedVertex(std::unordered_map<int, int>& mapping) {
    for (int v : vertices) {
        if (mapping.find(v) == mapping.end()) {
            return v;
        }
    }
    return -1; // Should not happen if the function is used correctly
}