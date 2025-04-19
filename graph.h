// sone0149@gmail.com
#ifndef GRAPH_H
#define GRAPH_H

#include <exception>
#include <stdexcept>

namespace graph {

    struct Edge {
        int dest;   // destination vertex
        int weight; // edge weight
        Edge() : dest(-1), weight(0) {}
        Edge(int d, int w) : dest(d), weight(w) {}
    };

    class Graph {
    private:
        int num_vertices;
        Edge** adj_list; // Array of arrays of Edges
        int* adj_sizes;  // Number of edges per vertex
        int* adj_capacities; // Capacity of each adjacency list

    public:
        Graph(int vertices);
        ~Graph();
        void addEdge(int src, int dest, int weight = 1);
        void removeEdge(int src, int dest);
        void print_graph() const;
        int getNumVertices() const { return num_vertices; }
        const Edge* getAdjList(int vertex, int& size) const { size = adj_sizes[vertex]; return adj_list[vertex]; }
    };

}

#endif