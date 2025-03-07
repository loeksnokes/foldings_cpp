#include "ggraph.hpp"
#include "graph.hpp" // Include graph.hpp to use Vertex::roll()
#include <iostream>
#include <queue>

GGraph::GGraph(int k, int n) : kmerLength(k), alphabetSize(n) {
    // Create a Graph (De Bruijn graph)
    auto deBruijnGraph = std::make_shared<Graph>(k, n);

    // Generate all possible k-mers
    std::vector<std::string> kmers;
    std::queue<std::string> q;
    for (int i = 0; i < alphabetSize; ++i) {
        q.push(std::string(1, '0' + i));
    }

    while (!q.empty()) {
        std::string current = q.front();
        q.pop();
        if (current.length() == k) {
            kmers.push_back(current);
        } else {
            for (int i = 0; i < alphabetSize; ++i) {
                q.push(current + std::string(1, '0' + i));
            }
        }
    }

    // Create vertices for each k-mer
    for (const auto& kmer : kmers) {
        auto vertex = std::make_shared<Vertex>();
        vertex->addString(kmer);
        deBruijnGraph->addVertex(vertex);
    }

    // Add the De Bruijn graph to the GGraph
    addVertex(deBruijnGraph);
}

void GGraph::addVertex(std::shared_ptr<Graph> v) {
    vertices.push_back(v);
    adjacencyList[v] = std::vector<std::shared_ptr<Graph>>(); // Initialize the adjacency list for the new vertex
}

void GGraph::addEdge(std::shared_ptr<Graph> src, std::shared_ptr<Graph> dst) {
    adjacencyList[src].push_back(dst);
}

void GGraph::removeVertex(std::shared_ptr<Graph> v) {
    // Remove from vertices list
    for (auto it = vertices.begin(); it != vertices.end(); ++it) {
        if (*it == v) {
            vertices.erase(it);
            break;
        }
    }

    // Remove from adjacency list (as a key)
    adjacencyList.erase(v);

    // Remove from adjacency lists (as a value)
    for (auto& pair : adjacencyList) {
        auto& neighbors = pair.second;
        for (auto it = neighbors.begin(); it != neighbors.end(); ) {
            if (*it == v) {
                it = neighbors.erase(it);
            } else {
                ++it;
            }
        }
    }
}

// Function to perform the folding operation
void GGraph::fold(int alphabetSize) {
    // Iterate through all pairs of vertices (graphs)
    for (auto& srcGraphPtr : vertices) {
        for (auto& destGraphPtr : vertices) {
            if (srcGraphPtr == destGraphPtr) continue; // Skip self-loops

            bool canFold = true;
            Graph& srcGraph = *srcGraphPtr;
            Graph& destGraph = *destGraphPtr;

            // Check if rolling the source vertex results in vertices contained in the destination vertex
            for (const auto& srcVertexPtr : srcGraph.getVertices()) {
                std::set<std::string> rolledKmers;
                srcVertexPtr->roll(alphabetSize, rolledKmers);
                bool allKmersPresent = true;

                // Check if all rolled k-mers are present in *any* vertex of the destination graph
                bool foundDestVertex = false;
                for (const auto& destVertexPtr : destGraph.getVertices()) {
                    bool allRolledKmersInDestVertex = true;
                    for (const auto& kmer : rolledKmers) {
                        if (!destVertexPtr->containsString(kmer)) {
                            allRolledKmersInDestVertex = false;
                            break;
                        }
                    }
                    if (allRolledKmersInDestVertex) {
                        foundDestVertex = true;
                        break;
                    }
                }
                if (!foundDestVertex) {
                    canFold = false;
                    break;
                }
            }

            if (canFold) {
                addEdge(srcGraphPtr, destGraphPtr);
            }
        }
    }
}