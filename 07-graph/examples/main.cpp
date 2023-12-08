#include <string>
#include <cstddef>
#include <iostream>
#include <vector>
#include <tuple>

#include "graph.hpp"
#include "topological_sort.hpp"
#include "dijkstra_shortest_paths.hpp"
#include "prim_minimum_spanning_tree.hpp"

int main(int argc, char *argv[]) {
    edges_t edges = {{0, 1, 1.0f}, {1, 2, 2.0f}};
    Graph(3, edges, GraphType::DIRECTED);
    return 0;
}
