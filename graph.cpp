// sone0149@gmail.com
#include "graph.h"
#include <iostream>

namespace graph {

Graph::Graph(int vertices) : num_vertices(vertices) {
    if (vertices <= 0) {
        throw std::invalid_argument("Number of vertices must be positive");
    }
    adj_list = new Edge*[vertices];
    adj_sizes = new int[vertices];
    adj_capacities = new int[vertices];
    for (int i = 0; i < vertices; ++i) {
        adj_sizes[i] = 0;
        adj_capacities[i] = 4; // Initial capacity
        adj_list[i] = new Edge[4];
    }
}

Graph::~Graph() {
    for (int i = 0; i < num_vertices; ++i) {
        delete[] adj_list[i];
    }
    delete[] adj_list;
    delete[] adj_sizes;
    delete[] adj_capacities;
}

void Graph::addEdge(int src, int dest, int weight) {
    if (src < 0 || src >= num_vertices || dest < 0 || dest >= num_vertices) {
        throw std::out_of_range("Vertex index out of range");
    }
    // Resize src adjacency list if needed
    if (adj_sizes[src] == adj_capacities[src]) {
        int new_capacity = adj_capacities[src] * 2;
        Edge* new_list = new Edge[new_capacity];
        for (int i = 0; i < adj_sizes[src]; ++i) {
            new_list[i] = adj_list[src][i];
        }
        delete[] adj_list[src];
        adj_list[src] = new_list;
        adj_capacities[src] = new_capacity;
    }
    // Resize dest adjacency list if needed
    if (adj_sizes[dest] == adj_capacities[dest]) {
        int new_capacity = adj_capacities[dest] * 2;
        Edge* new_list = new Edge[new_capacity];
        for (int i = 0; i < adj_sizes[dest]; ++i) {
            new_list[i] = adj_list[dest][i];
        }
        delete[] adj_list[dest];
        adj_list[dest] = new_list;
        adj_capacities[dest] = new_capacity;
    }
    adj_list[src][adj_sizes[src]++] = Edge(dest, weight);
    adj_list[dest][adj_sizes[dest]++] = Edge(src, weight); // Undirected
}

void Graph::removeEdge(int src, int dest) {
    if (src < 0 || src >= num_vertices || dest < 0 || dest >= num_vertices) {
        throw std::out_of_range("Vertex index out of range");
    }

    bool found = false;
    for (int i = 0; i < adj_sizes[src]; ++i) {
        if (adj_list[src][i].dest == dest) {
            for (int j = i; j < adj_sizes[src] - 1; ++j) {
                adj_list[src][j] = adj_list[src][j + 1];
            }
            adj_sizes[src]--;
            found = true;
            break;
        }
    }

    for (int i = 0; i < adj_sizes[dest]; ++i) {
        if (adj_list[dest][i].dest == src) {
            for (int j = i; j < adj_sizes[dest] - 1; ++j) {
                adj_list[dest][j] = adj_list[dest][j + 1];
            }
            adj_sizes[dest]--;
            break;
        }
    }

    if (!found) {
        throw std::runtime_error("Edge does not exist");
    }
}

void Graph::print_graph() const {
    for (int i = 0; i < num_vertices; ++i) {
        std::cout << "Vertex " << i << ": ";
        for (int j = 0; j < adj_sizes[i]; ++j) {
            std::cout << "(" << adj_list[i][j].dest << ", w=" << adj_list[i][j].weight << ") ";
        }
        std::cout << std::endl;
    }
}

}