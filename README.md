# CPP_EX1_25

## Overview

This project implements graph using an adjacency list. It includes implementations of the following graph algorithms:

- Breadth-First Search (BFS)
- Depth-First Search (DFS)
- Dijkstra's shortest path algorithm
- Prim's Minimum Spanning Tree (MST) algorithm
- Kruskal's Minimum Spanning Tree (MST) algorithm


## File Structure

- `graph.h`, `graph.cpp`: Graph class with basic operations (addEdge, removeEdge, print_graph).
- `algorithms.h`, `algorithms.cpp`: Implementations of graph algorithms.
- `queue.h`, `queue.cpp`: Basic queue implementation for BFS.
- `priority_queue.h`, `priority_queue.cpp`: Simple priority queue implementation for Dijkstra and Prim.
- `union_find.h`, `union_find.cpp`: Union-Find data structure with path compression and union by rank.
- `main.cpp`: Demonstration of graph usage and algorithm execution.
- `tests.cpp`: Unit tests using the Doctest library.
- `Makefile`: Build instructions, test execution, and memory leak checking.
- `doctest.h`: External testing library included in the project.

## Makefile Commands

- `make Main`: Compiles and builds the main program (`main.cpp`).
- `make test`: Runs unit tests from `tests.cpp`.
- `make valgrind`: Checks for memory leaks using Valgrind.
- `make clean`: Removes executable files (`Main`, `test`) and object files.



#
