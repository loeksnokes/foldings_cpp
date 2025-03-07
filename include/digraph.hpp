#ifndef DIGRAPH_HPP
#define DIGRAPH_HPP

#include <vector>
#include <unordered_map>
#include <memory> // Include for shared_ptr

class Digraph {
public:
    Digraph();

    void addVertex(int v);
    void addEdge(int src, int dst);

    bool IsDigraphIsomorphic(Digraph* g2);
    int nextUnmappedVertex(std::unordered_map<int, int>& mapping);

private:
    bool tryIsomorphism(int v1, std::vector<int>& vertices2, std::unordered_map<int, bool>& used, std::unordered_map<int, int>& mapping, Digraph* g2, int depth);
    bool checkConsistency(int v1, int v2, std::unordered_map<int, int>& mapping, Digraph* g2);

    std::vector<int> vertices;
    std::unordered_map<int, std::vector<int>> adjacencyList;
};

#endif