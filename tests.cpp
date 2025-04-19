// sone0149@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "graph.h"
#include "algorithms.h"

using namespace graph;

TEST_CASE("Graph operations") {
    Graph g(4);
    
    SUBCASE("Add edge") {
        CHECK_NOTHROW(g.addEdge(0, 1, 2));
        CHECK_NOTHROW(g.addEdge(1, 2, 3));
        CHECK_THROWS_AS(g.addEdge(0, 4, 1), std::out_of_range);
    }
    
    SUBCASE("Remove edge") {
        g.addEdge(0, 1, 2);
        CHECK_NOTHROW(g.removeEdge(0, 1));
        CHECK_THROWS_AS(g.removeEdge(0, 1), std::runtime_error);
        CHECK_THROWS_AS(g.removeEdge(0, 4), std::out_of_range);
    }
}

TEST_CASE("BFS") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 1);
    
    Graph bfs_tree = Algorithms::bfs(g, 0);
    CHECK(bfs_tree.getNumVertices() == 4);
    CHECK_THROWS_AS(Algorithms::bfs(g, 4), std::out_of_range);
}

TEST_CASE("DFS") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 1);
    
    Graph dfs_tree = Algorithms::dfs(g, 0);
    CHECK(dfs_tree.getNumVertices() == 4);
    CHECK_THROWS_AS(Algorithms::dfs(g, 4), std::out_of_range);
}

TEST_CASE("Dijkstra") {
    Graph g(4);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 1);
    
    Graph dijkstra_tree = Algorithms::dijkstra(g, 0);
    CHECK(dijkstra_tree.getNumVertices() == 4);
    CHECK_THROWS_AS(Algorithms::dijkstra(g, 4), std::out_of_range);
}

TEST_CASE("Prim") {
    Graph g(4);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 5);
    
    Graph prim_tree = Algorithms::prim(g);
    CHECK(prim_tree.getNumVertices() == 4);
}

TEST_CASE("Kruskal") {
    Graph g(4);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 5);
    
    Graph kruskal_tree = Algorithms::kruskal(g);
    CHECK(kruskal_tree.getNumVertices() == 4);
}