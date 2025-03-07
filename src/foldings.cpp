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
std::shared_ptr<Vertex> mergeVertices(Graph& g, std::shared_ptr<Vertex> v1, std::shared_ptr<Vertex> v2) {

    // Verify these two vertices currently belong to the graph.
    if (g.getVertices().find(v1) == g.getVertices().end() || g.getVertices().find(v2) == g.getVertices().end()) {
        return nullptr;
    }

    auto mergedVertex = std::make_shared<Vertex>();

    // Combine the string sets of v1 and v2
    for (const auto& str : v1->getKmers()) {
        mergedVertex->addString(str);
    }
    for (const auto& str : v2->getKmers()) {
        mergedVertex->addString(str);
    }

    // Add the merged vertex to the graph
    g.addVertex(mergedVertex);

    return mergedVertex;
}

// Function to fold the graph by merging vertices p and q
Graph fold(Graph& graph, std::shared_ptr<Vertex> p, std::shared_ptr<Vertex> q) {
    Graph foldedGraph(graph.getK(), graph.getK());

    // Initialize the queue with the initial pair (p, q)
    std::queue<std::pair<std::shared_ptr<Vertex>, std::shared_ptr<Vertex>>> queue;
    queue.push({p, q});
    std::map<std::shared_ptr<Vertex>, std::shared_ptr<Vertex>> processed;

    while (!queue.empty()) {
        auto pair = queue.front();
        queue.pop();

        std::shared_ptr<Vertex> v1 = pair.first;
        std::shared_ptr<Vertex> v2 = pair.second;

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
        std::shared_ptr<Vertex> mergedVertex = mergeVertices(foldedGraph, v1, v2);

        // Register the merged vertex in the processed map
        processed[v1] = mergedVertex;
        processed[v2] = mergedVertex;

        // Propagate the identification through the graph
        for (const auto& str : v1->getKmers()) {
            for (const auto& charr : graph.getAlphabet()) {
                if (str.length() > 1) {
                    std::string uPrime = str.substr(1) + charr;
                    bool v1Contains = false;
                    bool v2Contains = false;
                    for (const auto& v : graph.getVertices()) {
                        if (v->containsString(uPrime)) {
                            v1Contains = true;
                        }
                    }
                    for (const auto& v : graph.getVertices()) {
                        if (v->containsString(uPrime)) {
                            v2Contains = true;
                        }
                    }
                    std::shared_ptr<Vertex> uVertex;
                    std::shared_ptr<Vertex> vVertex;
                    for (const auto& v : graph.getVertices()) {
                        if (v->containsString(uPrime)) {
                            uVertex = v;
                        }
                    }
                    for (const auto& v : graph.getVertices()) {
                        if (v->containsString(uPrime)) {
                            vVertex = v;
                        }
                    }
                    if (v1Contains && v2Contains) {
                        queue.push({uVertex, vVertex});
                    }
                }
            }
        }
    }

    // Redirect edges and add them to the folded graph
    for (const auto& srcVertex : graph.getVertices()) {
        std::shared_ptr<Vertex> mergedSrc = processed[srcVertex];
        for (const auto& dst : graph.getNeighbors(srcVertex)) {
            std::shared_ptr<Vertex> mergedDst = processed[dst];
            if (mergedSrc && mergedDst) {
                foldedGraph.addEdge(mergedSrc, mergedDst);
            }
        }
    }

    // Remove the original vertices p and q from the graph G
    //foldedGraph.removeVertex(p);
    //foldedGraph.removeVertex(q);

    return foldedGraph;
}