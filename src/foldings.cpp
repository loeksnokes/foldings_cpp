// foldings.cpp
#include "graph.hpp"
#include "digraph.hpp"
#include "ggraph.hpp"
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <iostream>
#include <queue>

// Function to merge two vertices and create a new vertex
Vertex* mergeVertices(Graph& g, Vertex* v1, Vertex* v2) {
    Vertex* mergedVertex = new Vertex();

    // Combine the string sets of v1 and v2
    for (const auto& str : v1->stringsSet) {
        mergedVertex->addString(str.first);
    }
    for (const auto& str : v2->stringsSet) {
        mergedVertex->addString(str.first);
    }

    // Add the merged vertex to the graph
    g.addVertex(mergedVertex);

    return mergedVertex;
}

// Function to fold the graph by merging vertices p and q
Graph fold(Graph& graph, Vertex* p, Vertex* q) {
    Graph foldedGraph;

    // Initialize the queue with the initial pair (p, q)
    std::queue<std::pair<Vertex*, Vertex*>> queue;
    queue.push({p, q});
    std::map<Vertex*, Vertex*> processed;

    while (!queue.empty()) {
        auto pair = queue.front();
        queue.pop();

        Vertex* v1 = pair.first;
        Vertex* v2 = pair.second;

        // If either vertex has already been processed, skip
        if (processed.count(v1)) {
            processed[v2] = processed[v1];
            continue;
        }
        if (processed.count(v2)) {
            processed[v1] = processed[v2];
            continue;
        }

        // Merge the two vertices
        Vertex* mergedVertex = mergeVertices(foldedGraph, v1, v2);

        // Register the merged vertex in the processed map
        processed[v1] = mergedVertex;
        processed[v2] = mergedVertex;

        // Propagate the identification through the graph
        for (const auto& str : v1->stringsSet) {
            for (const auto& char : "01") {
                if (str.first.length() > 1) {
                    std::string uPrime = str.first.substr(1) + char;
                    if (v1->containsString(uPrime) && v2->containsString(uPrime)) {
                        Vertex* uVertex = findVertexContainingString(graph, uPrime);
                        Vertex* vVertex = findVertexContainingString(graph, uPrime);
                        queue.push({uVertex, vVertex});
                    }
                }
            }
        }
    }

    // Redirect edges and add them to the folded graph
    for (const auto& src : graph.adjacencyList) {
        Vertex* mergedSrc = processed[src.first];
        for (const auto& dst : src.second) {
            Vertex* mergedDst = processed[dst];
            if (mergedSrc && mergedDst) {
                foldedGraph.addEdge(mergedSrc, mergedDst);
            }
        }
    }

    // Remove the original vertices p and q from the graph G
    foldedGraph.removeVertex(p);
    foldedGraph.removeVertex(q);

    return foldedGraph;
}