// sone0149@gmail.com
#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <stdexcept>

namespace graph {

    class UnionFind {
    private:
        int* parent;
        int* rank;
        int size;

    public:
        UnionFind(int size);
        ~UnionFind();
        int find(int x);
        bool unite(int x, int y);
    };

}

#endif