#include "rbtree.hpp"

#include <iostream>
#include <random>
#include <vector>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "rbtree_test_util.hpp"

TEST_CASE("Black balance", "[rbtree]") {
    RBTree<int> rbtree;
    std::vector<int> xs;
    size_t n = 100'000;

    for (auto i = 0; i < n; i++)
        xs.emplace_back(i);

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(xs.begin(), xs.end(), g);

    for (auto i : xs)
        rbtree.insert(i);

    REQUIRE(test_black_balance(rbtree));
}

TEST_CASE("Inorder traversal", "[rbtree]") {
    std::vector<int> xs, ys, zs;
    RBTree<int> rbtree;
    size_t n = 100'000;

    for (auto i = 1; i <= n; i++) {
        xs.emplace_back(i);
        ys.emplace_back(i);
    }

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(xs.begin(), xs.end(), g);

    for (auto i : xs)
        rbtree.insert(i);

    rbtree.root->traverse_inorder([&zs](RBNode<int>* n) {
        zs.emplace_back(n->key);
    });

    REQUIRE(zs[0] == ys[0]);
    REQUIRE(zs[1] == ys[1]);
    REQUIRE(zs[2] == ys[2]);
    REQUIRE(zs == ys);
}

TEST_CASE("Left lean", "[rbtree]") {
    std::vector<int> xs, ys, zs;
    RBTree<int> rbtree;
    size_t n = 100'000;

    for (auto i = 1; i <= n; i++) {
        xs.emplace_back(i);
        ys.emplace_back(i);
    }

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(xs.begin(), xs.end(), g);

    for (auto i : xs)
        rbtree.insert(i);

    REQUIRE(test_left_lean(rbtree));
}
