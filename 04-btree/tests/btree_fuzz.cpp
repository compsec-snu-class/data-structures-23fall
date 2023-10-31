#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <random>

#include <openssl/sha.h>

#include "btree.hpp"

extern "C" int LLVMFuzzerTestOneInput(const char* data, size_t size) {
    BTree<unsigned char, 2> btree;
    unsigned char cs[20]; // The output size of sha1 has is 20 bytes
    std::vector<unsigned char> ds;

    SHA1((unsigned char*) data, size, cs);

    for (auto i = 0; i < 20; i++) {
        btree.insert(cs[i]);
        ds.push_back(cs[i]);
    }

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(ds.begin(), ds.end(), g);

    for (auto i = 0; i < 20; i++)
        btree.remove(ds[i]);

    return 0;
}
