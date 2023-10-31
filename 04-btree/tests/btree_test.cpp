#include <algorithm>
#include <iterator>
#include <vector>
#include <random>

#include "btree.hpp"

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("2-4 tree in-order traversal", "[btree]") {
    BTree<int, 2> tree;

    std::random_device rd;
    std::mt19937 g(rd());

    std::vector<int> ws;
    size_t N = 100'000;

    for (auto i = 1; i <= N; i++)
        ws.push_back(i);

    std::shuffle(ws.begin(), ws.end(), g);

    for (auto i = 0; i < N; i++)
        tree.insert(ws[i]);

    std::vector<int> xs, ys;

    for (auto i = 1; i <= N; i++)
        xs.push_back(i);

    tree.for_all([&](int& i){ ys.push_back(i); });

    REQUIRE(xs.size() == ys.size());
    for (auto i = 0u; i < xs.size(); i++)
        REQUIRE(xs[i] == ys[i]);
}

TEST_CASE("In-order traversal, and find_rightmost_key", "[btree]") {
    BTree<int> tree;
    std::vector<int> xs, ys, zs;
    size_t N = 1'000'000;

    /* Prepare a random vector */
    std::random_device rd;
    std::mt19937 g(rd());

    for (auto i = 1; i < N; i++) {
        xs.push_back(i);
        zs.push_back(i);
    }

    std::shuffle(xs.begin(), xs.end(), g);

    /* Insert a random sequence to the B-tree */
    for (auto i : xs)
        tree.insert(i);

    /* Iterate over the B-tree. Are the elements sorted? */
    tree.for_all([&](int& i){ ys.push_back(i); });

    REQUIRE(zs.size() == ys.size());
    for (auto i = 0u; i < zs.size(); i++)
        REQUIRE(zs[i] == ys[i]);
    REQUIRE(BTreeNode<int, 6>::find_rightmost_key(*(tree.root)) == N - 1);
}

TEST_CASE("Node utilization", "[btree]") {
    static constexpr size_t B = 10;
    BTree<int, B> btree;
    std::vector<int> xs;
    size_t n = 100'000;

    std::random_device rd;
    std::mt19937 g(rd());

    for (auto i = 1; i <= n; i++)
        xs.push_back(i);

    std::shuffle(xs.begin(), xs.end(), g);

    for (auto i : xs)
        btree.insert(i);

    std::vector<size_t> num_keys;

    /* Visit all nodes and collect the number of keys */
    btree.for_all_nodes([&num_keys](const BTreeNode<int, B>& bn) {
        num_keys.emplace_back(bn.n);
    });

    /* sum(# keys per nodes) should equal to the # keys that are inserted */
    auto total_num_keys =
        std::accumulate(num_keys.begin(), num_keys.end(), 0 /* sum */);

    REQUIRE(total_num_keys == n);

    /* All nodes (except one node) should contain # keys between B-1 and
       2B-1 */
    bool root_visited = false;
    REQUIRE(std::all_of(num_keys.begin(), num_keys.end(),
                        [&root_visited](auto num_keys){
                            if (B-1 <= num_keys && num_keys <= 2*B-1)
                                return true;
                            else if (!root_visited) {
                                /* One node (i.e., the root node) is allowed to
                                   have less than B-1 keys. */
                                root_visited = true;
                                return true;
                            } else {
                                return false;
                            }}));
}

TEST_CASE("Perfect balance") {
    static constexpr size_t B = 7;
    BTree<int, B> btree;
    std::vector<int> xs;
    size_t n = 10'000;

    std::random_device rd;
    std::mt19937 g(rd());

    for (auto i = 1; i <= n; i++)
        xs.push_back(i);

    std::shuffle(xs.begin(), xs.end(), g);

    for (auto i : xs)
        btree.insert(i);

    auto depth = btree.depth();

    REQUIRE(btree.find_rightmost_key().has_value());
    REQUIRE(btree.find_rightmost_key().value() == n);
    REQUIRE(depth.has_value());

    /* Test internal nodes */
    for (auto i = 0; i < depth.value(); i++) {
        auto nodes_at_level_i = btree.root->find_nodes_at_level(i);

        REQUIRE(std::all_of(nodes_at_level_i.begin(),
                            nodes_at_level_i.end(),
                            [](const BTreeNode<int, B>* n){
                                return n->type == NodeType::INTERNAL;
                            }));
    }


    /* Test leaf nodes */
    auto nodes_at_leaf_level = btree.root->find_nodes_at_level(depth.value());
    REQUIRE(std::all_of(nodes_at_leaf_level.begin(),
                        nodes_at_leaf_level.end(),
                        [](const BTreeNode<int, B>* n){
                            return n->type == NodeType::LEAF;
                        }));
}
