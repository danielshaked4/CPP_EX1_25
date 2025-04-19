// sone0149@gmail.com
#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "graph.h"

namespace graph {

    struct WeightedEdge {
        int weight;
        int src;
        int dest;
        WeightedEdge() : weight(0), src(-1), dest(-1) {} // Default constructor
        WeightedEdge(int w, int s, int d) : weight(w), src(s), dest(d) {}
    };

    const int MAX_INT = 2147483647;

    class Algorithms {
    public:
        static Graph bfs(const Graph& g, int source);
        static Graph dfs(const Graph& g, int source);
        static Graph dijkstra(const Graph& g, int source);
        static Graph prim(const Graph& g);
        static Graph kruskal(const Graph& g);
    };

}

#endif