#ifndef __RBTREE_TEST_UTIL_H_
#define __RBTREE_TEST_UTIL_H_

#include <algorithm>

#include "rbtree.hpp"

template <typename T>
bool is_red(const RBNode<T>* n) {
    return n && n->color == RED;
}

template<typename T>
bool test_left_lean(const RBTree<T>& rbtree) {
    auto res = true;

    if (!rbtree.root)
        return true;

    rbtree.root->traverse_inorder([&res](RBNode<int>* n) {
        if (is_red(n)) {
            if (RBNode<int>::is_red(n->right) ||
                RBNode<int>::is_red(n->left)) {
                /* No back-to-back red */
                res = false;
            }
        }

        if (RBNode<int>::is_red(n->right) &&
            !RBNode<int>::is_red(n->left)) {
            /* No right leaning node */
            res = false;
        }
    });

    return res;
}

template<typename T>
bool test_black_balance(const RBTree<T>& rbtree) {
    size_t num_black = 0;
    auto all_leaves = rbtree.collect_all_leaves();

    auto res = std::all_of(all_leaves.begin(), all_leaves.end(),
                           [&num_black](const auto& pn){
                               if (num_black == 0) {
                                   num_black = pn.first.num_black_;
                                   return true;
                               }

                               return num_black == pn.first.num_black_;
                           });

    return res;
}



#endif // __RBTREE_TEST_UTIL_H_
