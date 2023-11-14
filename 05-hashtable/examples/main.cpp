#include <iostream>
#include <vector>
#include <random>
#include <assert.h>

#include "hash_table.hpp"
#include "hash_funcs.hpp"

template <typename HT>
void basic_test(HT &ht) {
    int num_to_test = 3000;
    std::string value;
    bool result;

    unsigned long total_steps = 0;

    for (auto i=0; i<num_to_test; i++) {
        assert(ht.get_load_factor() <= 0.5);
        ht.put(i, std::to_string(i));
    }

    for (auto i=0; i<num_to_test; i++) {
        unsigned long steps = ht.get(i, value);
        total_steps += steps;
        assert(steps >= 0);
        assert(value == std::to_string(i));
    }

    assert(ht.remove(3) >= 0);
    assert(ht.get(3, value) == -1);

    assert(ht.remove(5) >= 0);
    assert(ht.get(5, value) == -1);
    
    std::cout << "[*] size: "<< ht.get_size() << std::endl;
    std::cout << "[*] table_size: "<< ht.get_table_size() << std::endl;
    std::cout << "[*] Load factor: "<< ht.get_load_factor() << std::endl;
}


#define LinearIntStrHt LinearProbeHashTable<int, std::string>
#define QuadIntStrHt QuadProbeHashTable<int, std::string>


int main() {
    HashFunc *hash_func = new DefaultHashFunc;

    LinearIntStrHt linear_basic_ht(hash_func);
    basic_test<LinearIntStrHt>(linear_basic_ht);

    QuadIntStrHt quad_basic_ht(hash_func);
    basic_test<QuadIntStrHt>(quad_basic_ht);
    
    delete hash_func;

    return 0;
}
