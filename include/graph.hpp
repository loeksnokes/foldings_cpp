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

class Vertex {
public:
    Vertex();
    Vertex(const std::set<std::string>& kmers);
    void addString(const std::string& s);
    bool containsString(const std::string& s) const;
    bool operator<(const Vertex& other) const;
    bool operator==(const std::string& other) const;
    void roll(int symbol, std::set<std::string>& rolledKmers) const;
    void print() const;
    std::set<std::string> getKmers() const;

private:
    std::set<std::string> stringsSet;
};

struct VertexPtrCompare {
    bool operator()(const std::shared_ptr<Vertex>& a, const std::shared_ptr<Vertex>& b) const {
        return *a < *b;
    }
};

class Graph {
public:
    Graph(int k, const std::vector<std::string>& alphabet);
    int getK() const { return kmerLength; }
    int getN() const { return alphabetSize; }
    const std::set<std::shared_ptr<Vertex>>& getVertices() const { return vertices; }
    void print() const;

    void addVertex(std::shared_ptr<Vertex> v);
    void addEdge(std::shared_ptr<Vertex> v1, std::shared_ptr<Vertex> v2);
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