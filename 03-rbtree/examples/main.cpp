#include <random>
#include <vector>
#include <algorithm>
#include <bitset>

#include "rbtree.hpp"

int main(int argc, char *argv[]) {
    std::vector<int> xs{};
    RBTree<int> rbtree{};
    size_t N = 99;

    for (auto i = 1; i <= N; i++)
        xs.emplace_back(i);

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(xs.begin(), xs.end(), g);

    for (auto i : xs) {
        rbtree.insert(i);
        std::cout << rbtree << '\n';
    }

    const auto& all_leaves = rbtree.collect_all_leaves();
    for (const auto &[p, n] : all_leaves)
        std::cout << "path: " << std::bitset<16>{p.p_}
                  << "\tlen: " << p.len_
                  << "\tblack: " << p.num_black_ << '\n';

    return 0;
}
