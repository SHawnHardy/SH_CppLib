/**
 * @file serialization_unitest.h
 * @version v0.1
 * @author SHawnHardy
 * @date 2019-01-10
 * @copyright MIT License
 */

#include <random>

#include <gtest/gtest.h>

#include "GraphTheory/graph.h"
#include "GraphTheory/serialization.h"

using namespace sh;

const int graph_size = 300;

TEST(SerializationTest, GraphAdjacencyMatrix) {
    std::random_device rd;
    std::uniform_int_distribution<> dis(0, graph_size - 1);
    std::set<std::pair<int, int>> st;

    GraphAdjacencyMatrix g(graph_size);
    for (int i = 0; i < graph_size * graph_size * 0.3; i++) {
        int a, b;
        do {
            a = dis(rd);
            b = dis(rd);
        } while (st.find(std::make_pair(a, b)) != st.end());
        st.insert(std::make_pair(a, b));
        g.addEdge(a, b);
    }

    std::ostringstream osm;
    serialize_GraphAdjacencyMatrix(g, osm);

    std::istringstream ism(osm.str());
    GraphAdjacencyMatrix *gg = deserialize_GraphAdjacencyMatrix(ism);

    for (int i = 0; i < graph_size; i++) {
        for (int j = 0; j < graph_size; j++) {
            ASSERT_EQ(gg->check(i, j), st.find(std::make_pair(i, j)) != st.end());
        }
    }
}

