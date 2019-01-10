/**
 * @file graph_with_data.h
 * @version v0.3
 * @author SHawnHardy
 * @date 2019-01-09
 * @copyright MIT License
 */

#ifndef SH_GRAPHTHEORY_GRAPH_WITH_DATA_H
#define SH_GRAPHTHEORY_GRAPH_WITH_DATA_H

#include <assert.h>
#include <iterator>
#include <vector>

namespace sh {
    template<typename _Tp>
    class GraphWithData {
    public:
        explicit GraphWithData(int size) : size_(size) {}

        virtual bool check(int a, int b) const = 0;

        virtual _Tp &addEdge(int a, int b, _Tp data) = 0;

        virtual _Tp delEdge(int a, int b) = 0;

        virtual void clear() = 0;

        virtual _Tp &get_data(int a, int b) const = 0;

        int get_size() const {
            return size_;
        }

    protected:
        const int size_ = 0;
    };

    template<typename _Tp>
    class GraphWithDataAdjacencyList : public GraphWithData<_Tp> {
    public:
        typedef std::pair<int, _Tp> DataType;
        typedef typename std::vector<DataType>::iterator Itrt;

        explicit GraphWithDataAdjacencyList(int size) : GraphWithData<_Tp>(size) {
            assert(size > 0);
            data_ = new std::vector<DataType>[GraphWithData<_Tp>::size_];
        }

        ~GraphWithDataAdjacencyList() {
            delete[] data_;
        }

        bool check(int a, int b) const override {
            assert(a < GraphWithData<_Tp>::size_ && b < GraphWithData<_Tp>::size_);
            for (auto &&data : data_[a]) {
                if (data.first == b)
                    return true;
            }
            return false;
        }

        _Tp &addEdge(int a, int b, _Tp data) override {
            assert(a < GraphWithData<_Tp>::size_ && b < GraphWithData<_Tp>::size_);
            assert(!check(a, b));
            data_[a].push_back(std::make_pair(b, data));
            return data_[a].back().second;
        }

        _Tp delEdge(int a, int b) override {
            assert(a < GraphWithData<_Tp>::size_ && b < GraphWithData<_Tp>::size_);
            auto itrt = data_[a].begin();
            while (itrt != data_[a].end() && (*itrt).first != b) {
                itrt++;
            }
            if (itrt == data_[a].end())
                exit(1);
            _Tp rt = (*itrt).second;
            data_[a].erase(itrt);
            return rt;
        }

        void clear() override {
            for (int i = 0; i < GraphWithData<_Tp>::size_; i++) {
                data_[i].clear();
            }
        }

        _Tp &get_data(int a, int b) const override {
            assert(a < GraphWithData<_Tp>::size_ && b < GraphWithData<_Tp>::size_);
            for (auto &&data : data_[a]) {
                if (data.first == b)
                    return data.second;
            }
            exit(1);
        }

        Itrt get_edges_begin(int a) const {
            return data_[a].begin();
        }

        Itrt get_edges_end(int a) const {
            return data_[a].end();
        }


    private:
        std::vector<DataType> *data_;
    };
}
#endif //SH_GRAPHTHEORY_GRAPH_WITH_DATA_H
