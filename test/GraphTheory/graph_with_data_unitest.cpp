/**
 * @file graph_with_data_unitest.h
 * @version v0.1
 * @author SHawnHardy
 * @date 2019-01-09
 * @copyright MIT License
 */

#include <assert.h>
#include <random>
#include <iostream>
#include <map>

#include <gtest/gtest.h>

#include <GraphTheory/graph_with_data.h>

using namespace sh;

const int graph_size = 300;

TEST(GraphWithDataTest, GraphWithDataAdjacencyList_initial) {
    GraphWithDataAdjacencyList<int> g(graph_size);
    ASSERT_EQ(g.get_size(), graph_size);

    for (int i = 0; i < graph_size; i++) {
        for (int j = 0; j < graph_size; j++) {
            ASSERT_FALSE(g.check(i, j));
        }
    }
}

TEST(GraphWithDataTest, GraphWithDataAdjacencyList_usage) {
    std::random_device rd;
    std::uniform_int_distribution<> dis(0, graph_size - 1);
    std::map<std::pair<int, int>, int> mp;

    GraphWithDataAdjacencyList<int> g(graph_size);

    for (int i = 0; i < graph_size * graph_size * 0.3; i++) {
        int a, b;
        do {
            a = dis(rd);
            b = dis(rd);
        } while (mp.find(std::make_pair(a, b)) != mp.end());
        int data = (a * 1000 + b) * 1000 + dis(rd);
        mp[std::make_pair(a, b)] = data;
        g.addEdge(a, b, data);
    }

    for (int i = 0; i < graph_size; i++) {
        for (int j = 0; j < graph_size; j++) {
            auto key = std::make_pair(i, j);
            if (g.check(i, j)) {
                ASSERT_TRUE(mp.find(key) != mp.end());
                ASSERT_EQ(g.get_data(i, j), mp[key]);
            } else {
                ASSERT_FALSE(mp.find(key) != mp.end());
            }
        }
    }

    int count = 1000;
    while (count--) {
        int op = dis(rd) % 3;
        int a, b;

        do {
            a = dis(rd);
            b = dis(rd);
        } while ((mp.find(std::make_pair(a, b)) != mp.end()) ^ (op > 0));


        int data = (a * 1000 + b) * 1000 + dis(rd);
        switch (op) {
            case 0: {
                mp[std::make_pair(a, b)] = data;
                int &tmp = g.addEdge(a, b, -data);
                ASSERT_EQ(g.get_data(a, b), -data);
                tmp *= -1;
                break;
            }
            case 1: {
                ASSERT_EQ(mp[std::make_pair(a, b)], g.get_data(a, b));
                mp[std::make_pair(a, b)] = data;
                g.get_data(a, b) = data;
                break;
            }
            case 2: {
                int tmp = g.delEdge(a, b);
                ASSERT_EQ(tmp, mp[std::make_pair(a, b)]);
                mp.erase(std::make_pair(a, b));

            }
        }

        for (int i = 0; i < graph_size; i++) {
            for (int j = 0; j < graph_size; j++) {
                auto key = std::make_pair(i, j);
                if (g.check(i, j)) {
                    ASSERT_TRUE(mp.find(key) != mp.end());
                    ASSERT_EQ(g.get_data(i, j), mp[key]);
                } else {
                    ASSERT_FALSE(mp.find(key) != mp.end());
                }
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


TEST(GraphWithDataTest, GraphWithDataAdjacencyList_get_edges) {
    std::random_device rd;
    std::uniform_int_distribution<> dis(0, graph_size - 1);
    std::map<std::pair<int, int>, int> mp;

    GraphWithDataAdjacencyList<int> g(graph_size);

    for (int i = 0; i < graph_size * graph_size * 0.3; i++) {
        int a, b;
        do {
            a = dis(rd);
            b = dis(rd);
        } while (mp.find(std::make_pair(a, b)) != mp.end());
        int data = (a * 1000 + b) * 1000 + dis(rd);
        mp[std::make_pair(a, b)] = data;
        g.addEdge(a, b, data);
    }

    for (int i = 0; i < graph_size; i++) {
        for (auto itr = g.get_edges_begin(i); itr != g.get_edges_end(i); itr++) {
            auto key = std::make_pair(i, (*itr).first);
            ASSERT_TRUE(mp.find(key) != mp.end());
            ASSERT_EQ(mp[key], (*itr).second);
            mp.erase(std::make_pair(i, (*itr).first));
        }
    }

    ASSERT_EQ(mp.size(), 0);
}

TEST(GraphWithDataTest, GraphWithDataAdjacencyList_death_test) {
    GraphWithDataAdjacencyList<int> g(graph_size);
    EXPECT_EXIT(g.delEdge(0, 0), testing::ExitedWithCode(1), "");
    EXPECT_EXIT(g.get_data(0, 0), testing::ExitedWithCode(1), "");
    g.addEdge(1, 1, 1);
    EXPECT_EXIT(g.addEdge(1, 1, 2), testing::ExitedWithCode(1), "");
}
