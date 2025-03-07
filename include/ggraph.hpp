#ifndef GGRAPH_HPP
#define GGRAPH_HPP

#include "graph.hpp" // Include the definition of Graph class
#include <vector>
#include <map>
#include <memory>  // Include for support of smart pointers.

/**
 * @brief Represents a graph of graphs, where vertices are Graph objects.
 */
class GGraph {
public:
    /**
     * @brief Constructor for the GGraph class that initializes the graph with a k-mer length and an alphabet.
     * @param k The length of the k-mers.
     * @param alphabet The alphabet to use for the k-mers.
     */
    GGraph(int k, int n);

    /**
     * @brief Adds a vertex (Graph object) to the GGraph.
     * @param v The vertex to add.
     */
    void addVertex(std::shared_ptr<Graph> v);

    /**
     * @brief Adds an edge between two vertices (Graph objects) in the GGraph.
     * @param src The source vertex.
     * @param dst The destination vertex.
     */
    void addEdge(std::shared_ptr<Graph> src, std::shared_ptr<Graph> dst);

    /**
     * @brief Removes a vertex (Graph object) from the GGraph.
     * @param v The vertex to remove.
     */
    void removeVertex(std::shared_ptr<Graph> v);

    /**
     * @brief Performs the folding operation on the GGraph.
     * @param alphabetSize The size of the alphabet to use for the folding operation.
     */
    void fold(int alphabetSize);

    /**
     * @brief Gets the set of vertices (Graph objects) in the GGraph.
     * @return The set of vertices.
     */
    const std::set<std::shared_ptr<Graph>>& getVertices() const;

private:
    std::map<std::shared_ptr<Graph>, std::vector<std::shared_ptr<Graph>>> adjacencyList;
    std::set<std::shared_ptr<Graph>> vertices;
    int kmerLength;
    std::vector<std::string> alphabet;
    int alphabetSize;
};

#endif