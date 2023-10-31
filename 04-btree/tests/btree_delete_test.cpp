#include <algorithm>
#include <iterator>
#include <vector>
#include <random>

#include "btree.hpp"

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("Delete", "[btree]") {
    BTree<int, 2> tree;
    size_t N = 100'000;

    std::vector<int> xs, ys;

    for (auto i = 1; i <= N; i++) {
        xs.push_back(i);
        ys.push_back(i);
    }

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(xs.begin(), xs.end(), g);
    std::shuffle(ys.begin(), ys.end(), g);

    for (auto i : xs)
        tree.insert(i);

    for (auto i : ys)
        tree.remove(i);

    REQUIRE(tree.root->n == 0);
}

TEST_CASE("Inorder traversal after deletion", "[btree]") {
    BTree<int> btree;
    std::vector<int> xs, ys, zs, ws;
    auto N = 100'000u;

    std::random_device rd;
    std::mt19937 g(rd());

    for (auto i = 1u; i <= N; i++) {
        xs.push_back(i);
        ys.push_back(i);
        if (i % 2 == 0)
            zs.push_back(i);
    }

    std::shuffle(xs.begin(), xs.end(), g);
    std::shuffle(ys.begin(), ys.end(), g);

    for (auto i : xs)
        btree.insert(i);

    /* Remove all odd numbers */
    for (auto i : ys)
        if (i % 2 != 0)
            btree.remove(i);

    /* In-order traversal */
    btree.for_all([&ws](int &i){ ws.push_back(i); });

    /* HACK to suppress test case failure report */
    REQUIRE(zs.size() == ws.size());
    for (auto i = 0u; i < zs.size(); i++)
        REQUIRE(zs[i] == ws[i]);
}

TEST_CASE("Node utilization after deletions", "[btree]") {
    static constexpr size_t B = 2;
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


    for (auto i : xs)
        if (i % 2 == 0)
            btree.remove(i);

    std::vector<size_t> num_keys;

    /* Visit all nodes and collect the number of keys */
    btree.for_all_nodes([&num_keys](const BTreeNode<int, B>& bn) {
        num_keys.emplace_back(bn.n);
    });

    /* sum(# keys per nodes) should equal to the # keys that are inserted */
    auto total_num_keys =
        std::accumulate(num_keys.begin(), num_keys.end(), 0 /* sum */);

    REQUIRE(total_num_keys == n / 2);

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
