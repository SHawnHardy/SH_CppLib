/**
 * @file serialization.h
 * @version v0.1
 * @author SHawnHardy
 * @date 2019-01-10
 * @copyright MIT License
 */

#ifndef SH_GRAPHTHEORY_SERIALIZATION_H
#define SH_GRAPHTHEORY_SERIALIZATION_H

#include "./graph.h"

namespace sh {
    void serialize_GraphAdjacencyMatrix(const sh::GraphAdjacencyMatrix &g, std::ostream &osm) {
        int size = g.get_size();
        osm << size << std::endl;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (g.check(i, j)) {
                    osm << i << ' ' << j << std::endl;
                }
            }
        }
    }

    sh::GraphAdjacencyMatrix *deserialize_GraphAdjacencyMatrix(std::istream &ism) {
        int size = 0;
        ism >> size;
        auto g = new sh::GraphAdjacencyMatrix(size);
        int s, t;
        while (ism >> s >> t) {
            g->addEdge(s, t);
        }
        return g;
    }
}
#endif //SH_GRAPHTHEORY_SERIALIZATION_H
