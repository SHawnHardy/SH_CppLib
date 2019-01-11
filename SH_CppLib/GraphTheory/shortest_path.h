/**
 * @file shortest_path.h
 * @version v0.1
 * @author SHawnHardy
 * @date 2019-01-11
 * @copyright MIT License
 */

#ifndef SH_GRAPHTHEORY_SHORTEST_PATH_H
#define SH_GRAPHTHEORY_SHORTEST_PATH_H

#include <algorithm>
#include <queue>

#include "./graph.h"

namespace sh {
    void floydWarshall(const sh::Graph &g, int *ans[]) {
        int size = g.get_size();
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                ans[i][j] = (i == j ? 0 : (g.check(i, j) ? 1 : -1));
            }
        }

        for (int k = 0; k < size; k++) {
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    if ((ans[i][k] != -1) && (ans[k][j] != -1)) {
                        if (ans[i][j] == -1) {
                            ans[i][j] = ans[i][k] + ans[k][j];
                        } else {
                            ans[i][j] = std::min(ans[i][j], ans[i][k] + ans[k][j]);
                        }
                    }
                }
            }
        }
    }

    void bidirectionalSearch(const sh::Graph &g, int a, int ans[]) {
        int size = g.get_size();
        bool *vis = new bool[size]();
        for (int i = 0; i < size; i++) {
            ans[i] = -1;
        }
        ans[a] = 0;
        vis[a] = true;

        std::queue<int> q;
        q.push(a);

        while (!q.empty()) {
            int now = q.front();
            q.pop();
            for (int i = 0; i < size; i++) {
                if ((!vis[i]) && (g.check(now, i))) {
                    vis[i] = true;
                    ans[i] = ans[now] + 1;
                    q.push(i);
                }
            }
        }
        delete[] vis;
    }
}

#endif //SH_GRAPHTHEORY_SHORTEST_PATH_H
