#include <algorithm>
#include <iterator>
#include <vector>
#include <random>
#include <string>

#include "hash_table.hpp"
#include "hash_funcs.hpp"

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>


#define LinearIntStrHt LinearProbeHashTable<int, std::string>
#define QuadIntStrHt QuadProbeHashTable<int, std::string>

template <typename HT>
void simple_test(HT &htable) {
    REQUIRE(htable.put(1, "1") > 0);
    REQUIRE(htable.put(2, "2") > 0);
    REQUIRE(htable.put(3, "3") > 0);

    std::string value;
    REQUIRE(htable.get(2, value) > 0);
    REQUIRE(value == "2");

    REQUIRE(htable.get(3, value) > 0);
    REQUIRE(value == "3");

    REQUIRE(htable.remove(3) > 0);
    REQUIRE(htable.get(3, value) == -1);
}

TEST_CASE("hashtable simple test", "[hashtable]") {
    HashFunc *hash_func = new DefaultHashFunc;
    
    LinearIntStrHt linear_ht(hash_func);
    simple_test<LinearIntStrHt>(linear_ht);

    QuadIntStrHt quad_ht(hash_func);
    simple_test<QuadIntStrHt>(quad_ht);

    delete hash_func;
}

template <typename HT>
void enlarge_insert_test(HT &htable) {
    int num_to_test = 10000;
    std::string value;

    htable.get_table_size() == INITIAL_TABLE_SIZE;

    for (auto i=0; i<num_to_test; i++) {
        REQUIRE(htable.put(i, std::to_string(i)) > 0);
        REQUIRE(htable.get_load_factor() <= 0.5);
    }
    REQUIRE(htable.get_size() == num_to_test);

    for (auto i=0; i<num_to_test; i++) {
        REQUIRE(htable.get(i, value) > 0);
        REQUIRE(value == std::to_string(i));
    }
}

TEST_CASE("hashtable enlarge insert", "[hashtable]") {
    HashFunc *hash_func = new DefaultHashFunc;

    LinearIntStrHt linear_ht(hash_func);
    enlarge_insert_test<LinearIntStrHt>(linear_ht);

    QuadIntStrHt quad_ht(hash_func);
    enlarge_insert_test<QuadIntStrHt>(quad_ht);

    delete hash_func;
}


template <typename HT>
void enlarge_remove_test(HT &htable) {
    int num_to_test = 10000;
    std::string value;

    htable.get_table_size() == INITIAL_TABLE_SIZE;

    for (auto i=0; i<num_to_test; i++) {
        REQUIRE(htable.put(i, std::to_string(i)) > 0);
        REQUIRE(htable.get_load_factor() <= 0.5);
    }
    REQUIRE(htable.get_size() == num_to_test);

    for (auto i=0; i<num_to_test; i++) {
        REQUIRE(htable.get(i, value) > 0);
        REQUIRE(value == std::to_string(i));
    }

    REQUIRE(htable.get_size() == num_to_test);

    for (auto i=0; i<num_to_test; i++) {
        REQUIRE(htable.remove(i) > 0);
        REQUIRE(htable.get(i, value) == -1);

        REQUIRE(htable.get_size() == num_to_test-i-1);
        REQUIRE(htable.get_load_factor() <= 0.5);
    }

    REQUIRE(htable.get_size() == 0);
}

TEST_CASE("hashtable enlarge remove", "[hashtable]") {
    HashFunc *hash_func = new DefaultHashFunc;

    LinearIntStrHt linear_ht(hash_func);
    enlarge_remove_test<LinearIntStrHt>(linear_ht);

    QuadIntStrHt quad_ht(hash_func);
    enlarge_remove_test<QuadIntStrHt>(quad_ht);

    delete hash_func;
}

template <typename HT>
void rand_test(HT &htable) {
    int num_to_insert = 3000;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1,num_to_insert/10);

    generator.seed(0);
    for (auto i=0; i<=num_to_insert; i++) {
      int k = distribution(generator);
      std::string v = std::to_string(i);
      htable.put(k, v);
    }

    generator.seed(0);    
    for (auto i=0; i<=num_to_insert; i++) {
      int k = distribution(generator);
      std::string v;
      int res = htable.get(k, v);
      if (res > 0) {
        REQUIRE(v == std::to_string(i));
        htable.remove(k);
      }
    }
}

TEST_CASE("hashtable rand test", "[hashtable]") {
    HashFunc *hash_func = new DefaultHashFunc;

    LinearIntStrHt linear_ht(hash_func);
    rand_test<LinearIntStrHt>(linear_ht);

    QuadIntStrHt quad_ht(hash_func);
    rand_test<QuadIntStrHt>(quad_ht);

    delete hash_func;
}

template <typename HT>
void probe_test(HT &ht, bool is_linear) {
    int num_to_test = INITIAL_TABLE_SIZE/2;
    int arr[num_to_test];
    unsigned long total_steps = 0;

    int after_cluster = 0;
    for (auto i=0; i<num_to_test; i++) {
        if (i < num_to_test/2)
            arr[i] = i*INITIAL_TABLE_SIZE;
        else
            arr[i] = ++after_cluster;
    }

    after_cluster = 0;
    for (auto i=0; i<num_to_test; i++) {
        int step = ht.put(arr[i], std::to_string(arr[i]));

        std::string v;
        REQUIRE(step == ht.get(arr[i], v));
        REQUIRE(v == std::to_string(arr[i]));

        if (i < num_to_test/2)
            REQUIRE(step == i+1);
        else {
            if (is_linear)
                REQUIRE(step == (num_to_test/2));
            else
                REQUIRE(step < num_to_test/4);
        }
        total_steps += step;
    }
}

TEST_CASE("hashtable probe test", "[hashtable]") {
    HashFunc *hash_func = new DefaultHashFunc;

    LinearIntStrHt linear_ht(hash_func);
    probe_test<LinearIntStrHt>(linear_ht, true);

    QuadIntStrHt quad_ht(hash_func);
    probe_test<QuadIntStrHt>(quad_ht, false);

    delete hash_func;
}
