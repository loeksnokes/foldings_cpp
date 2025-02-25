#ifndef DIGRAPH_HPP
#define DIGRAPH_HPP

#include <vector>
#include <map>

class Digraph {
public:
    Digraph();

    void addVertex(int v);
    void addEdge(int src, int dst);

private:
    std::map<int, std::vector<int>> adjacencyList;
    std::vector<int> vertices;
};

#endif // DIGRAPH_HPP