#ifndef GGRAPH_HPP
#define GGRAPH_HPP

#include "graph.hpp" // Include the definition of Graph class
#include <vector>
#include <map>
#include <memory> // Include for shared_ptr

class GGraph {
public:
    GGraph(int k, int n); // Constructor takes k and n

    void addVertex(std::shared_ptr<Graph> v);
    void addEdge(std::shared_ptr<Graph> src, std::shared_ptr<Graph> dst);
    void removeVertex(std::shared_ptr<Graph> v);
    void fold(int alphabetSize);

private:
    std::map<std::shared_ptr<Graph>, std::vector<std::shared_ptr<Graph>>> adjacencyList;
    std::vector<std::shared_ptr<Graph>> vertices;
    int kmerLength;
    int alphabetSize;
};

#endif // GGRAPH_HPP