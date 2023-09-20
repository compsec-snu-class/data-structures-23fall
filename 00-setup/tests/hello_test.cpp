#include <vector>

#include "hello.hpp"

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("It works", "[Hello]") {
    REQUIRE(2 + 2 == 4);
}

TEST_CASE("Calculator works!", "[Hello]") {
    IntCalculator calc;

    REQUIRE(calc.add(2, 2) == 4);
}

