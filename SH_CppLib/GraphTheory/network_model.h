/**
 * @file network_model.h
 * @version v0.1
 * @author SHawnHardy
 * @date 2019-01-11
 * @copyright MIT License
 */

#ifndef SH_GRAPHTHEORY_NETWORK_MODEL_H
#define SH_GRAPHTHEORY_NETWORK_MODEL_H

#include "./graph.h"

namespace sh {
    void buildRegularNetwork(Graph &g, const int start, const int size, const int param_k) {
        for (int i = 0; i < size; i++) {
            for (int j = 1; j <= param_k; j++) {
                g.addEdge(start + i, start + (i + j) % size);
                g.addEdge(start + i, start + (i + size - j) % size);
            }
        }
    }

    void buildWattsStrogatzNetwork(Graph &g, const int start, const int size,
                                   const int param_k, const double param_pr_retry) {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<> uniform_int_dtb(0, size - 1);
        std::uniform_real_distribution<double> uniform_real_dtb(0.0, 1.0);

        buildRegularNetwork(g, start, size, param_k);
        for (int i = 0; i < param_k; i++) {
            for (int neu_s = 0; neu_s < size; neu_s++) {
                if (uniform_real_dtb(mt) < param_pr_retry) {
                    int neu_t = (neu_s - param_k + i + size) % size;
                    g.delEdge(start + neu_s, start + neu_t);
                    g.delEdge(start + neu_t, start + neu_s);

                    int new_neu_t = uniform_int_dtb(mt);
                    while (new_neu_t == neu_s || new_neu_t == neu_t || g.check(start + neu_s, start + new_neu_t)) {
                        new_neu_t = uniform_int_dtb(mt);
                    }
                    g.addEdge(start + neu_s, start + new_neu_t);
                    g.addEdge(start + new_neu_t, start + neu_s);
                }
            }
        }
    }

    void coupleLayers(Graph &g,
                      const int layer_a_start, const int layer_a_size,
                      const int layer_b_start, const int layer_b_size,
                      const double param_pr_link) {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> uniform_real_dtb(0.0, 1.0);

        for (int i = 0; i < layer_a_size; i++) {
            for (int j = 0; j < layer_b_size; j++) {
                if (uniform_real_dtb(mt) < param_pr_link) {
                    g.addEdge(layer_a_start + i, layer_b_start + j);
                    g.addEdge(layer_b_start + j, layer_a_start + i);
                }
            }
        }
    }

    void buildPartialTimeDelayNetwork(const Graph &g, const int start, const int size, GraphWithData<bool> &gd,
                                      const double param_pr_time_delay) {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> uniform_real_dtb(0.0, 1.0);

        for (int i = 0; i < (size - 1); i++) {
            for (int j = (i + 1); j < size; j++) {
                if (g.check(start + i, start + j)) {
                    bool is_delay = uniform_real_dtb(mt) < param_pr_time_delay;
                    gd.addEdge(i, j, is_delay);
                    gd.addEdge(j, i, is_delay);
                }
            }
        }
    }
}

#endif //SH_GRAPHTHEORY_NETWORK_MODEL_H
