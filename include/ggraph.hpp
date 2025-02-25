#ifndef GGRAPH_HPP
#define GGRAPH_HPP

#include "graph.hpp"
#include <vector>
#include <map>

class GGraph {
public:
    GGraph();

    void addVertex(Graph* v);
    void addEdge(Graph* src, Graph* dst);
    void removeVertex(Graph* v);

private:
    std::map<Graph*, std::vector<Graph*>> adjacencyList;
    std::vector<Graph*> vertices;
};

#endif // GGRAPH_HPP