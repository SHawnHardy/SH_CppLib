/**
 * @file shortest_path_unitest.cpp
 * @version v0.1
 * @author SHawnHardy
 * @date 2019-01-11
 * @copyright MIT License
 */

#include <random>
#include <set>
#include <gtest/gtest.h>

#include "GraphTheory/graph.h"
#include "GraphTheory/shortest_path.h"

using namespace sh;

const int graph_size = 300;

TEST(ShortestPathTest, Graph_ShortestPath) {
    std::random_device rd;
    std::uniform_int_distribution<> dtb(0, graph_size - 1);
    std::set<std::pair<int, int>> st;

    GraphAdjacencyMatrix g(graph_size);

    for (int i = 0; i < graph_size * graph_size * 0.15; i++) {
        int a, b;
        do {
            a = dtb(rd);
            b = dtb(rd);
        } while (st.find(std::make_pair(a, b)) != st.end());
        st.insert(std::make_pair(a, b));
        g.addEdge(a, b);
    }

    int **floyd_ans = new int*[graph_size];
    for (int i = 0; i < graph_size; i++) {
        floyd_ans[i] = new int[graph_size];
    }

    floydWarshall(g, floyd_ans);

    int *bds_ans = new int[graph_size];
    for (int i = 0; i < graph_size; i++) {
        bidirectionalSearch(g, i, bds_ans);
        for (int j = 0; j < graph_size; j++) {
            ASSERT_EQ(floyd_ans[i][j], bds_ans[j]);
        }
    }
}
