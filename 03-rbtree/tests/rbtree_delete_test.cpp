#include "rbtree.hpp"

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "rbtree_test_util.hpp"

TEST_CASE("Remove max", "[rbtree]") {
    std::vector<int> xs;
    std::random_device rd;
    std::mt19937 g(rd());
    RBTree<int> rbtree;
    auto N = 1'000u;

    for (auto i = 0; i < N; i++)
        xs.push_back(i + 1);

    std::shuffle(xs.begin(), xs.end(), g);

    for (auto x : xs)
        rbtree.insert(x);

    for (auto i = 0; i < N; i++) {
        REQUIRE(rbtree.rightmost_key().value() == N - i);

        rbtree.remove_max();

        REQUIRE(test_left_lean(rbtree));
        REQUIRE(test_black_balance(rbtree));
    }
}

TEST_CASE("Remove min", "[rbtree]") {
    std::vector<int> xs;
    std::random_device rd;
    std::mt19937 g(rd());
    RBTree<int> rbtree;
    auto N = 1'000u;

    for (auto i = 0; i < N; i++)
        xs.push_back(i + 1);

    std::shuffle(xs.begin(), xs.end(), g);

    for (auto x : xs)
        rbtree.insert(x);

    for (auto i = 0; i < N; i++) {
        REQUIRE(rbtree.leftmost_key().value() == i + 1);

        rbtree.remove_min();

        REQUIRE(test_left_lean(rbtree));
        REQUIRE(test_black_balance(rbtree));
    }
}

TEST_CASE("Black balance after random deletions", "[rbtree]") {
    RBTree<int> rbtree;
    size_t n = 1'000;

    std::vector<int> xs;

    for (auto i = 0; i < n; i++)
        xs.emplace_back(i);

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(xs.begin(), xs.end(), g);

    for (auto x : xs)
        rbtree.insert(x);

    for (auto j = 0; j < xs.size(); j++) {
        if (j > xs[j]) {
            REQUIRE(rbtree.contains(xs[j]));
            rbtree.remove(xs[j]);
            REQUIRE(!rbtree.contains(xs[j]));

            auto is_left_lean = test_left_lean(rbtree);
            REQUIRE(is_left_lean);

            auto is_black_balance = test_black_balance(rbtree);
            REQUIRE(is_black_balance);
        }

    }

    REQUIRE(test_left_lean(rbtree));
    REQUIRE(test_black_balance(rbtree));
}

TEST_CASE("Inorder traversal after random deletions", "[rbtree]") {
    std::vector<int> xs, ys, zs;
    RBTree<int> rbtree;
    size_t n = 1'000;

    for (auto i = 1; i <= n; i++) {
        xs.emplace_back(i);
        ys.emplace_back(i);
    }

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(xs.begin(), xs.end(), g);

    for (auto i : xs)
        rbtree.insert(i);

    auto num_removed = 0u;
    for (auto j = 0; j < xs.size(); j++) {
        if (j > xs[j]) {
            rbtree.remove(xs[j]);
            num_removed++;
            std::remove(ys.begin(), ys.end(), xs[j]);
        }
    }

    ys.resize(ys.size() - num_removed);

    rbtree.root->traverse_inorder([&zs](RBNode<int>* n) {
        zs.emplace_back(n->key);
    });

    REQUIRE(zs[0] == ys[0]);
    REQUIRE(zs[1] == ys[1]);
    REQUIRE(zs[2] == ys[2]);
    REQUIRE(zs == ys);
}
