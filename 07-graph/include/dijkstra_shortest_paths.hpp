#ifndef __DIJKSTRA_SHORTEST_PATHS_H_
#define __DIJKSTRA_SHORTEST_PATHS_H_

#include <unordered_map>
#include <optional>
#include <tuple>
/* Feel free to add more standard library headers */

#include "graph.hpp"


/* Given a vertex `v`, `dijkstra_shortest_path` is:
 * - `nullopt` if `v` is not reacheble from `src`.
 * - {`u`, `d`} where `u` is the predecessor of `v` and `d` is the distance
 *   from `src`
 */

std::unordered_map<vertex_t,
    std::optional<std::tuple<vertex_t, edge_weight_t>>>
dijkstra_shortest_path(Graph& g, vertex_t src) {
    return {};
}

#endif // __DIJKSTRA_SHORTEST_PATHS_H_
