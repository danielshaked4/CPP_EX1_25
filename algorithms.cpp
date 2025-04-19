// sone0149@gmail.com
#include "algorithms.h"
#include "queue.h"
#include "priority_queue.h"
#include "union_find.h"

namespace graph {

// quicksort for WeightedEdge array
static int partition(WeightedEdge* arr, int low, int high) {
    WeightedEdge pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j].weight <= pivot.weight) {
            ++i;
            WeightedEdge temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    WeightedEdge temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

static void quicksort(WeightedEdge* arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

Graph Algorithms::bfs(const Graph& g, int source) {
    if (source < 0 || source >= g.getNumVertices()) {
        throw std::out_of_range("Source vertex out of range");
    }

    Graph tree(g.getNumVertices());
    bool* visited = new bool[g.getNumVertices()];
    for (int i = 0; i < g.getNumVertices(); ++i) {
        visited[i] = false;
    }
    Queue q(g.getNumVertices());

    visited[source] = true;
    q.push(source);

    while (!q.empty()) {
        int current = q.pop();
        int size;
        const Edge* edges = g.getAdjList(current, size);
        for (int i = 0; i < size; ++i) {
            int neighbor = edges[i].dest;
            int weight = edges[i].weight;
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
                tree.addEdge(current, neighbor, weight);
            }
        }
    }

    delete[] visited;
    return tree;
}

// DFS helper function
static void dfs_util(Graph& tree, bool* visited, const Graph& g, int vertex) {
    visited[vertex] = true;
    int size;
    const Edge* edges = g.getAdjList(vertex, size);
    for (int i = 0; i < size; ++i) {
        int neighbor = edges[i].dest;
        int weight = edges[i].weight;
        if (!visited[neighbor]) {
            tree.addEdge(vertex, neighbor, weight);
            dfs_util(tree, visited, g, neighbor);
        }
    }
}

Graph Algorithms::dfs(const Graph& g, int source) {
    if (source < 0 || source >= g.getNumVertices()) {
        throw std::out_of_range("Source vertex out of range");
    }

    Graph tree(g.getNumVertices());
    bool* visited = new bool[g.getNumVertices()];
    for (int i = 0; i < g.getNumVertices(); ++i) {
        visited[i] = false;
    }

    dfs_util(tree, visited, g, source);
    delete[] visited;
    return tree;
}

Graph Algorithms::dijkstra(const Graph& g, int source) {
    if (source < 0 || source >= g.getNumVertices()) {
        throw std::out_of_range("Source vertex out of range");
    }

    Graph tree(g.getNumVertices());
    int* dist = new int[g.getNumVertices()];
    int* parent = new int[g.getNumVertices()];
    PriorityQueue pq(g.getNumVertices());

    for (int i = 0; i < g.getNumVertices(); ++i) {
        dist[i] = MAX_INT;
        parent[i] = -1;
    }

    dist[source] = 0;
    pq.push(source, 0);

    while (!pq.empty()) {
        PriorityQueue::Node node = pq.pop();
        int distance = node.distance;
        int vertex = node.vertex;

        if (distance > dist[vertex]) continue;

        int size;
        const Edge* edges = g.getAdjList(vertex, size);
        for (int i = 0; i < size; ++i) {
            int neighbor = edges[i].dest;
            int weight = edges[i].weight;

            if (dist[vertex] + weight < dist[neighbor]) {
                dist[neighbor] = dist[vertex] + weight;
                parent[neighbor] = vertex;
                pq.push(neighbor, dist[neighbor]);
            }
        }
    }

    for (int i = 0; i < g.getNumVertices(); ++i) {
        if (parent[i] != -1) {
            int size;
            const Edge* edges = g.getAdjList(i, size);
            for (int j = 0; j < size; ++j) {
                if (edges[j].dest == parent[i]) {
                    tree.addEdge(i, parent[i], edges[j].weight);
                    break;
                }
            }
        }
    }

    delete[] dist;
    delete[] parent;
    return tree;
}

Graph Algorithms::prim(const Graph& g) {
    Graph tree(g.getNumVertices());
    bool* in_mst = new bool[g.getNumVertices()];
    int* key = new int[g.getNumVertices()];
    int* parent = new int[g.getNumVertices()];
    PriorityQueue pq(g.getNumVertices());

    for (int i = 0; i < g.getNumVertices(); ++i) {
        in_mst[i] = false;
        key[i] = MAX_INT;
        parent[i] = -1;
    }

    key[0] = 0;
    pq.push(0, 0);

    while (!pq.empty()) {
        PriorityQueue::Node node = pq.pop();
        int u = node.vertex;

        if (in_mst[u]) continue;

        in_mst[u] = true;

        if (parent[u] != -1) {
            int size;
            const Edge* edges = g.getAdjList(u, size);
            for (int i = 0; i < size; ++i) {
                if (edges[i].dest == parent[u]) {
                    tree.addEdge(u, parent[u], edges[i].weight);
                    break;
                }
            }
        }

        int size;
        const Edge* edges = g.getAdjList(u, size);
        for (int i = 0; i < size; ++i) {
            int v = edges[i].dest;
            int weight = edges[i].weight;

            if (!in_mst[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push(v, key[v]);
            }
        }
    }

    delete[] in_mst;
    delete[] key;
    delete[] parent;
    return tree;
}

Graph Algorithms::kruskal(const Graph& g) {
    Graph tree(g.getNumVertices());
    int max_edges = g.getNumVertices() * (g.getNumVertices() - 1) / 2;
    WeightedEdge* edges = new WeightedEdge[max_edges];
    int edge_count = 0;

    for (int u = 0; u < g.getNumVertices(); ++u) {
        int size;
        const Edge* adj = g.getAdjList(u, size);
        for (int i = 0; i < size; ++i) {
            if (u < adj[i].dest) {
                edges[edge_count++] = WeightedEdge(adj[i].weight, u, adj[i].dest);
            }
        }
    }

    if (edge_count > 0) {
        quicksort(edges, 0, edge_count - 1);
    }

    UnionFind uf(g.getNumVertices());

    for (int i = 0; i < edge_count; ++i) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int weight = edges[i].weight;
        if (uf.find(u) != uf.find(v)) {
            tree.addEdge(u, v, weight);
            uf.unite(u, v);
        }
    }

    delete[] edges;
    return tree;
}

}