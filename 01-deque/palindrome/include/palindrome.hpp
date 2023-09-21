#include <string>

#include "deque.hpp"

template<typename Deque>
class Palindrome {
public:
    bool is_palindrome(const std::string&);
    void reset_deque();

private:
    Deque deque;
};

template<typename Deque>
bool Palindrome<Deque>::is_palindrome(const std::string& s1) {
    // TODO
    return false;
}

template<typename Deque>
void Palindrome<Deque>::reset_deque() {
    while (!deque.empty())
        deque.remove_front();
}
