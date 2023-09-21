#include "palindrome.hpp"

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("Is palindrome? ArrayDeque", "[palindrome]") {
    Palindrome<ArrayDeque<char>> p;

    std::string s{"able was I ere I saw elba"};

    REQUIRE(p.is_palindrome(s));

    s += '.';

    REQUIRE(!p.is_palindrome(s));
}

TEST_CASE("Is palindrome? ListDeque", "[palindrome]") {
    Palindrome<ListDeque<char>> p;

    std::string s{"able was I ere I saw elba"};

    REQUIRE(p.is_palindrome(s));

    s += '.';

    REQUIRE(!p.is_palindrome(s));
}
