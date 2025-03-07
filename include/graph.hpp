#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <set>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <iostream>

// Forward declaration of GGraph
class GGraph;

/**
 * @brief Represents a vertex in a graph, storing a set of k-mers.
 */
class Vertex {
public:
    /**
     * @brief Default constructor for the Vertex class.
     */
    Vertex();

    /**
     * @brief Adds a string to the vertex.
     * @param s The string to add.
     */
    void addString(const std::string& s);

    /**
     * @brief Checks if the vertex contains a given string.
     * @param s The string to check for.
     * @return True if the vertex contains the string, false otherwise.
     */
    bool containsString(const std::string& s) const;

    /**
     * @brief Less-than operator for Vertex objects, used for comparing vertices.
     * @param other The other Vertex object to compare to.
     * @return True if this vertex is less than the other vertex, false otherwise.
     */
    bool operator<(const Vertex& other) const;

    /**
     * @brief Equality operator for Vertex objects, used for comparing vertices.
     * @param other The other Vertex object to compare to.
     * @return True if this vertex is equal to the other vertex, false otherwise.
     */
    bool operator==(const Vertex& other) const;

    /**
     * @brief Rolls the k-mers in the vertex by appending a symbol and removing the first character.
     * @param symbol The symbol to append (represented as an integer).
     * @param rolledKmers The set to store the rolled k-mers.
     */
    void roll(int symbol, std::set<std::string>& rolledKmers) const;

    /**
     * @brief Gets the set of k-mers stored in the vertex.
     * @return The set of k-mers.
     */
    std::set<std::string> getKmers() const;

private:
    std::set<std::string> stringsSet;
};

/**
 * @brief Functor for comparing shared pointers to Vertex objects.
 */
struct VertexPtrCompare {
    bool operator()(const std::shared_ptr<Vertex>& a, const std::shared_ptr<Vertex>& b) const {
        return *a < *b;
    }
};

/**
 * @brief Represents a graph, storing vertices and edges.
 */
class Graph {
public:
    /**
     * @brief Constructor for the Graph class that initializes the graph with a k-mer length and an alphabet.
     * @param k The length of the k-mers.
     * @param n The alphabet to use for the k-mers.
     */
    Graph(int k, int n);

    /**
     * @brief verify that the vertex belongs to the graph.
     *
     * @param v
     * @return true
     * @return false
     */
    bool containsVertex(const std::shared_ptr<Vertex> v) const;

    /**
     * @brief Gets the k-mer length of the graph.
     * @return The k-mer length.
     */
    int getK() const;

    /**
     * @brief Gets the alphabet size of the graph.
     * @return The alphabet size.
     */
    int getN() const;

    /**
     * @brief Gets the set of vertices in the graph.
     * @return The set of vertices.
     */
    const std::set<std::shared_ptr<Vertex>, VertexPtrCompare>& getVertices() const;

    /**
     * @brief Gets the vector of vertices that are adjacent to a given vertex.
     * @param v The vertex to get the neighbors of.
     * @return A const reference to the vector of adjacent vertices.
     */
    const std::vector<std::shared_ptr<Vertex>>& getNeighbors(const std::shared_ptr<Vertex> v) const;

    /**
     * @brief Gets the alphabet of the graph.
     * @return The alphabet of the graph.
     */
    const std::vector<std::string>& getAlphabet() const { return alphabet; }

    /**
     * @brief Adds a vertex to the graph.
     * @param v The vertex to add.
     */
    void addVertex(std::shared_ptr<Vertex> v);

    /**
     * @brief Adds an edge between two vertices in the graph.
     * @param v1 The first vertex.
     * @param v2 The second vertex.
     */
    void addEdge(std::shared_ptr<Vertex> v1, std::shared_ptr<Vertex> v2);

    /**
     * @brief Checks if two vertices are adjacent in the graph.
     * @param v1 The first vertex.
     * @param v2 The second vertex.
     * @return True if the vertices are adjacent, false otherwise.
     */
    bool areAdjacent(const std::shared_ptr<Vertex> v1, const std::shared_ptr<Vertex> v2) const;

    //Digraph generateDigraphCopy() const;

private:
    std::set<std::shared_ptr<Vertex>, VertexPtrCompare> vertices;
    std::map<std::shared_ptr<Vertex>, std::vector<std::shared_ptr<Vertex>>> adjacencyList;
    int kmerLength;
    std::vector<std::string> alphabet;
    int alphabetSize;
};

#endif