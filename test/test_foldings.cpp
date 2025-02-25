#include <gtest/gtest.h>
#include "../include/graph.hpp"
#include "../include/digraph.hpp"
#include "../include/ggraph.hpp"
#include "../src/foldings.cpp"

class FoldingsTest : public ::testing::Test {
protected:
    Graph* graph;
    Vertex* v1;
    Vertex* v2;

    void SetUp() override {
        graph = new Graph();
        v1 = new Vertex();
        v2 = new Vertex();
        v1->addString("state1");
        v2->addString("state2");
        graph->addVertex(v1);
        graph->addVertex(v2);
        graph->addEdge(v1, v2);
    }

    void TearDown() override {
        delete graph;
        delete v1;
        delete v2;
    }
};

TEST_F(FoldingsTest, TestMergeVertices) {
    Vertex* merged = graph->mergeVertices(v1, v2);
    EXPECT_TRUE(merged->containsString("state1"));
    EXPECT_TRUE(merged->containsString("state2"));
}

TEST_F(FoldingsTest, TestFold) {
    Graph* foldedGraph = fold(graph, v1, v2);
    EXPECT_EQ(foldedGraph->vertices.size(), 1);
    EXPECT_TRUE(foldedGraph->vertices[0]->containsString("state1"));
    EXPECT_TRUE(foldedGraph->vertices[0]->containsString("state2"));
}

TEST_F(FoldingsTest, TestIsValidFolding) {
    EXPECT_TRUE(isValidFolding(graph, 2, 2));
}

TEST_F(FoldingsTest, TestFindVertexContainingString) {
    Vertex* foundVertex = findVertexContainingString(graph, "state1");
    EXPECT_EQ(foundVertex, v1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}