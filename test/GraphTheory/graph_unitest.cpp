/**
 * @file graph_unitest.cpp
 * @version v0.1
 * @author SHawnHardy
 * @date 2019-01-08
 * @copyright MIT License
 */

#include <random>
#include <iostream>
#include <set>

#include <gtest/gtest.h>

#include "GraphTheory/graph.h"

using namespace sh;

const int graph_size = 300;

TEST(GraphTest, GraphAdjacencyMatrix_initial) {
    GraphAdjacencyMatrix g(graph_size);
    ASSERT_EQ(g.get_size(), graph_size);

    for (int i = 0; i < graph_size; i++) {
        for (int j = 0; j < graph_size; j++) {
            ASSERT_FALSE(g.check(i, j));
        }
    }
}

TEST(GraphTest, GraphAdjacencyMatrix_usage) {
    std::random_device rd;
    std::uniform_int_distribution<> dtb(0, graph_size - 1);
    std::set<std::pair<int, int>> st;

    GraphAdjacencyMatrix g(graph_size);

    for (int i = 0; i < graph_size * graph_size * 0.3; i++) {
        int a, b;
        do {
            a = dtb(rd);
            b = dtb(rd);
        } while (st.find(std::make_pair(a, b)) != st.end());
        st.insert(std::make_pair(a, b));
        g.addEdge(a, b);
    }

    for (int i = 0; i < graph_size; i++) {
        for (int j = 0; j < graph_size; j++) {
            ASSERT_EQ(g.check(i, j), st.find(std::make_pair(i, j)) != st.end());
        }
    }

    int count = 300;
    while (count--) {
        int op = dtb(rd);
        int a = dtb(rd);
        int b = dtb(rd);

        if (op & 1) {
            st.insert(std::make_pair(a, b));
            g.addEdge(a, b);
        } else {
            st.erase(std::make_pair(a, b));
            g.delEdge(a, b);
        }

        for (int i = 0; i < graph_size; i++) {
            for (int j = 0; j < graph_size; j++) {
                ASSERT_EQ(g.check(i, j), st.find(std::make_pair(i, j)) != st.end());
            }
        }
    }

    g.clear();
    for (int i = 0; i < graph_size; i++) {
        for (int j = 0; j < graph_size; j++) {
            ASSERT_FALSE(g.check(i, j));
        }
    }
}
