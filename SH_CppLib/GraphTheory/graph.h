/**
 * @file graph.h
 * @version v0.2
 * @author SHawnHardy
 * @date 2018-10-16
 * @copyright MIT License
 */

#ifndef SH_GRAPH_THEORY_GRAPH_H
#define SH_GRAPH_THEORY_GRAPH_H

#include <assert.h>
#include <iostream>
#include <iterator>
#include <vector>

class Graph {
public:
    explicit Graph(int size) : size_(size) {}

    virtual bool check(int a, int b) const = 0;

    virtual void addEdge(int a, int b) = 0;

    virtual void delEdge(int a, int b) = 0;

    virtual void clear() = 0;

    int get_size() {
        return size_;
    }

protected:
    const int size_ = 0;
};

class GraphAdjacencyMatrix : public Graph {
public:
    explicit GraphAdjacencyMatrix(int size) : Graph(size) {
        assert(size > 0);
        data_ = new bool *[size_];
        for (int i = 0; i < size_; i++) {
            data_[i] = new bool[size_]();
        }
    }

    ~GraphAdjacencyMatrix() {
        for (int i = 0; i < Graph::size_; i++) {
            delete[] data_[i];
        }
        delete[] data_;
    }

    bool check(int a, int b) const override {
        assert(a < size_ && b < size_);
        return data_[a][b];
    }

    void addEdge(int a, int b) override {
        assert(a < size_ && b < size_);
        data_[a][b] = true;
    }

    void delEdge(int a, int b) override {
        assert(a < size_ && b < size_);
        data_[a][b] = false;
    }

    void clear() override {
        for (int i = 0; i < size_; i++) {
            for (int j = 0; j < size_; j++) {
                data_[i][j] = false;
            }
        }
    }

private:
    bool **data_ = nullptr;
};


#endif //SH_GRAPH_THEORY_GRAPH_H
