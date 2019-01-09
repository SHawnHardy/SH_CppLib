/**
 * @file graph_unitest.cpp
 * @version v0.1
 * @author SHawnHardy
 * @date 2019-01-08
 * @copyright MIT License
 */

#include <assert.h>
#include <random>
#include <iostream>
#include <string>
#include <set>

#include <gtest/gtest.h>

#include <GraphTheory/graph.h>

const int graph_size = 200;

class GraphTest : public ::testing::Test {

protected:
    void SetUp() override {
        std::random_device rd;
        std::uniform_int_distribution<> dis(0, graph_size - 1);
        for (int i = 0; i < (int) (graph_size * 0.3); i++) {
            int a, b;
            do {
                a = dis(rd);
                b = dis(rd);
            } while (st.find(std::make_pair(a, b)) != st.end());
            st.insert(std::make_pair(a, b));
        }
    }

    std::set<std::pair<int, int>> st;
};

TEST_F(GraphTest, GraphAdjacencyMatrix_initial) {
    GraphAdjacencyMatrix g(graph_size);
    ASSERT_EQ(g.get_size(), graph_size);

    for (int i = 0; i < graph_size; i++) {
        for (int j = 0; j < graph_size; j++) {
            ASSERT_FALSE(g.check(i, j));
        }
    }
}

TEST_F(GraphTest, GraphAdjacencyMatrix_addEdge) {
    GraphAdjacencyMatrix g(graph_size);
    for (auto &&i : st) {
        g.addEdge(i.first, i.second);
    }
    for (int i = 0; i < graph_size; i++) {
        for (int j = 0; j < graph_size; j++) {
            bool flag = st.find(std::make_pair(i, j)) != st.end();
            ASSERT_EQ(g.check(i, j), flag);
        }
    }
}
