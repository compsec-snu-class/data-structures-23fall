#include <vector>

#include "deque.hpp"

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("Construction", "[ArrayDeque]") {
    ArrayDeque<int> ad;
    REQUIRE(ad.size() == 0);
    REQUIRE(ad.capacity() == 64);
    REQUIRE(ad.empty() == true);
}

TEST_CASE("Simple Push Front", "[ArrayDeque]") {
    ArrayDeque<int> ad;
    ad.push_front(10);
    ad.push_front(20);
    ad.push_front(30);

    REQUIRE(ad.remove_front() == 30);
}

TEST_CASE("Simple Push Back", "[ArrayDeque]") {
    ArrayDeque<int> ad;
    ad.push_back(10);
    ad.push_back(20);
    ad.push_back(30);

    REQUIRE(ad.remove_back() == 30);
}

TEST_CASE("Push with Resize", "[ArrayDeque]") {
    ArrayDeque<int> ad;
    for(int i = 0 ; i < 64 ; ++i) {
        ad.push_front(i);
    }
    ad.push_back(64);

    SECTION("Deque capacity changed") {
        REQUIRE(ad.capacity() == 128);
    }

    SECTION("Deque size remain") {
        REQUIRE(ad.size() == 65);
    }

    SECTION("Deque property holds") {
        REQUIRE(ad.remove_back() == 64);
    }
}

TEST_CASE("Random Push test", "[ArrayDeque]") {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0,1);

    ArrayDeque<int> ad;
    std::deque<int> deq;


    for(int i = 0 ; i < 10000 ; ++i) {
        if(dis(gen)) {
           // push_front
            ad.push_front(i);
            deq.emplace_front(i);
        }
        else {
           // push_back
            ad.push_back(i);
            deq.emplace_back(i);
        }
    }

    for(int i = 0 ; i < 10000 ; ++i) {
        REQUIRE(ad.remove_front() == deq[i]);
    }
}

TEST_CASE("Simple Remove Front", "[ArrayDeque]") {
    ArrayDeque<int> ad;

    ad.push_front(10);
    ad.push_front(20);
    ad.push_front(30);
    REQUIRE(ad.remove_front() == 30);
    REQUIRE(ad.remove_front() == 20);
    REQUIRE(ad.remove_front() == 10);
}

 TEST_CASE("Simple Remove Back", "[ArrayDeque]") {
     ArrayDeque<int> ad;

     ad.push_back(10);
     ad.push_back(20);
     ad.push_back(30);
     REQUIRE(ad.remove_back() == 30);
     REQUIRE(ad.remove_back() == 20);
     REQUIRE(ad.remove_back() == 10);
 }

TEST_CASE("Remove in Empty Deque", "[ArrayDeque]") {
    ArrayDeque<int> ad;

    REQUIRE(ad.remove_front() == std::nullopt);
    REQUIRE(ad.remove_back() == std::nullopt);

    ad.push_front(10);
    ad.remove_back();

    REQUIRE(ad.remove_front() == std::nullopt);
    REQUIRE(ad.remove_back() == std::nullopt);
}



TEST_CASE("Empty", "[ArrayDeque]") {
    ArrayDeque<int> ad;

    for(int i = 0 ; i < 256 ; ++i) {
        ad.push_back(i);
    }

    REQUIRE(ad.empty() == false);

    for(int i = 0 ; i < 256 ; ++i) {
        ad.remove_front();
    }
    REQUIRE(ad.empty() == true);
}

TEST_CASE("Index operation", "[ArrayDeque]") {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0,1);

    ArrayDeque<int> ad;
    std::deque<int> deq;

    for(int i = 0 ; i < 10000 ; ++i) {
        if(dis(gen)) {
           // push_front
            ad.push_front(i);
            deq.emplace_front(i);
        }
        else {
           // push_back
            ad.push_back(i);
            deq.emplace_back(i);
        }
    }

    std::cout << '\n';
    SECTION("should return correct value") {
        for(int i = 0 ; i < 10000 ; ++i) {
            REQUIRE(ad[i] == deq[i]);
        }
    }

    //TODO: How to check assertion fail?
    //SECTION("should fail if out of index") {
    //    REQUIRE_THROWS(ad[10000]);
    //}
}

TEST_CASE("It works", "[deque]") {
    REQUIRE(2 + 2 == 4);
}

TEST_CASE("An empty ListDeque", "[deque]") {
    ListDeque<int> xs;

    REQUIRE(xs.size() == 0);
    REQUIRE(xs.empty());
}

TEST_CASE("Push front", "[deque]") {
    ListDeque<int> deque;
    size_t N = 1000;

    for (auto i = 1; i <= N; i++)
        deque.push_front(i);

    REQUIRE(deque.size() == N);
    REQUIRE(!deque.empty());

    /* Forward iteration */
    auto after_a_cycle = deque.sentinel;
    for (auto i = 0; i <= N; i++)
        after_a_cycle = after_a_cycle->next;

    REQUIRE(after_a_cycle == deque.sentinel);

    /* Backward iteration */
    after_a_cycle = deque.sentinel;
    for (auto i = 0; i <= N; i++)
        after_a_cycle = after_a_cycle->prev;

    REQUIRE(after_a_cycle == deque.sentinel);
}

TEST_CASE("Push back", "[deque]") {
    ListDeque<int> deque;
    size_t N = 1000;

    for (auto i = 1; i <= N; i++)
        deque.push_back(i);

    REQUIRE(deque.size() == N);
    REQUIRE(!deque.empty());

    /* Forward iteration */
    auto after_a_cycle = deque.sentinel;
    for (auto i = 0; i <= N; i++)
        after_a_cycle = after_a_cycle->next;

    REQUIRE(after_a_cycle == deque.sentinel);

    /* Backward iteration */
    after_a_cycle = deque.sentinel;
    for (auto i = 0; i <= N; i++)
        after_a_cycle = after_a_cycle->prev;

    REQUIRE(after_a_cycle == deque.sentinel);
}

TEST_CASE("Remove front", "[deque]") {
    ListDeque<int> deque1, deque2;
    std::vector<int> xs, ys;
    size_t N = 1000;

    for (auto i = 1; i <= N; i++) {
        deque1.push_front(i);
        deque2.push_front(i);
    }

    auto it = deque2.sentinel->next;
    while (!deque1.empty()) {
        xs.emplace_back(deque1.remove_front().value());
        ys.emplace_back(it->value.value());
        it = it->next;
    }

    REQUIRE(xs == ys);
    REQUIRE(deque1.empty());
    REQUIRE(deque1.size() == 0);
}


TEST_CASE("Remove back", "[deque]") {
    ListDeque<int> deque1, deque2;
    std::vector<int> xs, ys;
    size_t N = 1000;

    for (auto i = 1; i <= N; i++) {
        deque1.push_front(i);
        deque2.push_front(i);
    }

    auto it = deque2.sentinel->prev;
    while (!deque1.empty()) {
        xs.emplace_back(deque1.remove_back().value());
        ys.emplace_back(it->value.value());
        it = it->prev;
    }

    REQUIRE(xs == ys);
    REQUIRE(deque1.empty());
    REQUIRE(deque1.size() == 0);
}

TEST_CASE("Index operator", "[deque]") {
    ListDeque<int> deque;
    size_t N = 1000, j = 42;

    for (auto i = 1; i <= N; i++)
        deque.push_back(i);

    /* Read */
    REQUIRE(deque[j] == j + 1);

    /* Write */
    deque[j] = j + 1337;
    auto it = deque.sentinel->next;
    for (auto k = 0; k < j; k++, it = it->next)
        ;

    REQUIRE(it->value.value() == j + 1337);
}
