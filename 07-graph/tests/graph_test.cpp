#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "graph.hpp"
#include <limits>

#include "dijkstra_shortest_paths.hpp"


/* This assignment only provides a small set of examples to test your
 * program, and our grading will test your code with other graph
 * inputs as well. So passing the provided test alone does not mean
 * that you will get the full score. So try to correctly implement
 * each graph algorithm, not just trying to pass this provide test!
*/

TEST_CASE("dijkstra_shortest_path", "[graph]") {
    SECTION("Example 1", "dijkstra 1") {
        edges_t dijkstra_edges1 = {{0, 1, 3.0f},
                                   {0, 2, 1.0f},
                                   {1, 2, 7.0f},
                                   {1, 3, 5.0f},
                                   {1, 4, 1.0f},
                                   {2, 3, 2.0f},
                                   {3, 4, 7.0f}};

        Graph g1(5, dijkstra_edges1, GraphType::UNDIRECTED);
        std::unordered_map<vertex_t,
                           std::optional<std::tuple<vertex_t,
                                                    edge_weight_t>>> dijkstra_result
            = dijkstra_shortest_path(g1, 2);

        // We do not check the source vertex's parent and distance
        std::vector<vertex_t> parent_answer = {2, 0, (vertex_t)-1, 2, 1};
        std::vector<edge_weight_t> dist_answer = {1.0f, 4.0f, 0.0f, 2.0f, 5.0f};

        for(size_t i = 0 ; i < 5 ; ++i) {
            if(i == 2)
                continue;
            REQUIRE(std::get<0>(dijkstra_result[i].value()) == parent_answer[i]);

            // Use epsilon to compare floating-point values.  Check
            // https://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
            // for more details.
            REQUIRE(
                fabs(std::get<1>(dijkstra_result[i].value()) - dist_answer[i])
                < std::numeric_limits<edge_weight_t>::epsilon());
        }
    }
}

#include "prim_minimum_spanning_tree.hpp"

TEST_CASE("prim_minimum_spanning_tree", "[graph]") {
    SECTION("Example 1", "MST exists") {
        edges_t prim_edges = {{0, 1, 4.0f},
                              {0, 7, 8.0f},
                              {1, 2, 8.0f},
                              {1, 7, 11.0f},
                              {2, 3, 7.0f},
                              {2, 8, 2.0f},
                              {2, 5, 4.0f},
                              {3, 4, 9.0f},
                              {3, 5, 14.0f},
                              {4, 5, 10.0f},
                              {5, 6, 2.0f},
                              {6, 7, 1.0f},
                              {6, 8, 6.0f},
                              {7, 8, 7.0f}};

        Graph g(9, prim_edges, GraphType::UNDIRECTED);
        std::optional<edges_t> prim_result
            = prim_minimum_spanning_tree(g, 0);

        // 1. This graph has MST.
        REQUIRE(prim_result != std::nullopt);

        std::unordered_map<vertex_t, bool> visited;
        edge_weight_t weight = 0;
        for(size_t i = 0 ; i < 9 ; ++i)
            visited[i] = false;


        // 2. Check if the returned results are a spanning tree
        for(auto edge : prim_result.value()) {
            vertex_t src = std::get<0>(edge);
            vertex_t dst = std::get<1>(edge);

            // If both src and dst vertices were already visisted, the
            // returned edges are not MST
            REQUIRE(!(visited[src] && visited[dst]));

            if(!visited[src])
                visited[src] = true;
            if(!visited[dst])
                visited[dst] = true;
            weight += std::get<2>(edge);
        }

        // 2. Every node should be visited to be MST
        for(size_t i = 0 ; i < 9 ; ++i)
            REQUIRE(visited[i] == true);

        // 3. Weight should be minimum to be MST
        REQUIRE(fabs(weight - 37.0f) < std::numeric_limits<edge_weight_t>::epsilon());
    }
}

#include "topological_sort.hpp"

TEST_CASE("topological_sort", "[graph]") {
    SECTION("Example 1", "Very Simple Case") {
        edges_t topological_edges = {{0, 1, 1.0f},
                                     {1, 2, 2.0f},
                                     {2, 3, 2.0f},
                                     {3, 4, 2.0f},
                                     {4, 5, 2.0f}};

        Graph g(8, topological_edges, GraphType::DIRECTED);
        std::vector<vertex_t> topological_result
            = topological_sort(g);
        std::vector<vertex_t> answer = {0, 1, 2, 3, 4, 5};
        REQUIRE(topological_result == answer);
    }
}
