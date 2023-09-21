#include "deque.hpp"
#include "palindrome.hpp"

int main(int argc, char *argv[]) {
    ListDeque<int> xs;

    for (auto i = 1; i <= 10; i++) {
        xs.push_back(i);
        std::cout << xs << '\n';
    }

    for (auto i = 10; i <= 20; i++) {
        xs.push_front(i);
        std::cout << xs << '\n';
    }

    auto np = xs.sentinel->prev;
    while (np != xs.sentinel) {
        std::cout << np->value.value() << ' ';
        np = np->prev;
    }
    std::cout << '\n';

    for (auto i = 0; i < 10; i++)
        std::cout << xs.remove_front().value_or(-1) << '\n'
                  << xs << '\n'
                  << "size: " << xs.size() << '\n';

    for (auto i = 0; i < 10; i++)
        std::cout << xs.remove_back().value_or(-1) << '\n'
                  << xs << '\n'
                  << "size: " << xs.size() << '\n';

    return 0;
}
