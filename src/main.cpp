#include <iostream>
#include <vector>
#include <string>
#include "graph.hpp"
#include "digraph.hpp"
#include "ggraph.hpp"

// Function to generate De Bruijn graph
Graph generateDeBruijnGraph(int k, const std::vector<std::string>& alphabet);

// Function to build the foldings graph
GGraph buildFoldingsGraph(Graph& G, int k, int n);

// Function to check if two digraphs are isomorphic
bool isDigraphIsomorphic(const Digraph& g1, const Digraph& g2);

int main() {
    std::vector<std::string> alphabet = {"0", "1"};
    int kLarge = 3;

    // Generate the large De Bruijn graph
    Graph graphLarge = generateDeBruijnGraph(kLarge, alphabet);
    Graph graphSmall = generateDeBruijnGraph(kLarge - 1, alphabet);
    Digraph digraphSmall = graphSmall.generateDigraphCopy();

    std::cout << "Original Large Graph:" << std::endl;
    graphLarge.print();

    // Generate the graph of all foldings
    GGraph foldingsGraph = buildFoldingsGraph(graphLarge, kLarge, alphabet.size());

    int kk = 1;
    for (const auto& vertex : foldingsGraph.getVertices()) {
        Digraph thisDigraph = vertex.generateDigraphCopy();
        if (isDigraphIsomorphic(thisDigraph, digraphSmall)) {
            std::string fstring = "folded_graph_" + std::to_string(kk);
            vertex.toDot(fstring);
            std::cout << "\nFolded Graph:" << std::endl;
            vertex.print();
            kk++;
        }
    }

    return 0;
}