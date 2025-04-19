// sone0149@gmail.com
#include "graph.h"
#include "algorithms.h"
#include <iostream>
#include <exception>

using namespace graph;

int main() {
    try {
        Graph g(5);

        g.addEdge(0, 1, 2);
        g.addEdge(0, 2, 4);
        g.addEdge(1, 2, 1);
        g.addEdge(1, 3, 5);
        g.addEdge(2, 3, 8);
        g.addEdge(2, 4, 3);
        g.addEdge(3, 4, 6);

        std::cout << "Original Graph:" << std::endl;
        g.print_graph();

        std::cout << "\nBFS Tree:" << std::endl;
        Graph bfs_tree = Algorithms::bfs(g, 0);
        bfs_tree.print_graph();

        std::cout << "\nDFS Tree:" << std::endl;
        Graph dfs_tree = Algorithms::dfs(g, 0);
        dfs_tree.print_graph();

        std::cout << "\nDijkstra Tree:" << std::endl;
        Graph dijkstra_tree = Algorithms::dijkstra(g, 0);
        dijkstra_tree.print_graph();

        std::cout << "\nPrim:" << std::endl;
        Graph prim_tree = Algorithms::prim(g);
        prim_tree.print_graph();

        std::cout << "\nKruskal:" << std::endl;
        Graph kruskal_tree = Algorithms::kruskal(g);
        kruskal_tree.print_graph();

        std::cout << "\nRemoving edge (0,1):" << std::endl;
        g.removeEdge(0, 1);
        g.print_graph();

    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}