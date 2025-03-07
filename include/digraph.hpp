#ifndef DIGRAPH_HPP
#define DIGRAPH_HPP

#include <vector>
#include <unordered_map>
#include <memory> // Include for shared_ptr

/**
 * @brief Represents a directed graph.
 */
class Digraph {
public:
    /**
     * @brief Default constructor for the Digraph class.
     */
    Digraph();

    /**
     * @brief Adds a vertex to the digraph.
     * @param v The vertex to add.
     */
    void addVertex(int v);

    /**
     * @brief Adds a directed edge from src to dst.
     * @param src The source vertex.
     * @param dst The destination vertex.
     */
    void addEdge(int src, int dst);

    /**
     * @brief Checks if two digraphs are isomorphic.
     * @param g2 The other digraph to compare to.
     * @return True if the digraphs are isomorphic, false otherwise.
     */
    bool IsDigraphIsomorphic(Digraph* g2);

    /**
     * @brief Finds the next unmapped vertex in the digraph.
     * @param mapping The current mapping of vertices.
     * @return The next unmapped vertex, or -1 if all vertices are mapped.
     */
    int nextUnmappedVertex(std::unordered_map<int, int>& mapping);

private:
    /**
     * @brief Tries to find an isomorphism between two digraphs using a recursive approach.
     */
    bool tryIsomorphism(int v1, std::vector<int>& vertices2, std::unordered_map<int, bool>& used, std::unordered_map<int, int>& mapping, Digraph* g2, int depth);

    /**
     * @brief Checks the consistency of a mapping between two vertices.
     */
    bool checkConsistency(int v1, int v2, std::unordered_map<int, int>& mapping, Digraph* g2);

    std::vector<int> vertices;
    std::unordered_map<int, std::vector<int>> adjacencyList;
};

#endif