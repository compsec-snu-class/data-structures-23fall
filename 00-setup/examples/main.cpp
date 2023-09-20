#include <iostream>
#include <optional>
#include <memory>

#include "hello.hpp"

std::optional<int> try_divide(int, int);

struct A {
    int a_;

    A() : a_(0) { std::cout << "default ctor A(" << a_ << ")\n"; }
    A(int a) : a_(a) { std::cout << "ctor A(" << a_ << ")\n"; }
    ~A() { std::cout << "dtor A(" << a_ << ")\n"; }
};

int main(int argc, char *argv[]) {
    IntCalculator calc;

    std::cout << "3 + 4 = " << calc.add(3, 4) << '\n';

    /* std::optional */
    if (try_divide(15, 3))
        std::cout << try_divide(15, 3).value() << '\n';

    auto opt = try_divide(17, 4);
    if (!opt)
        std::cout << "4 does not divice 17!\n";

    /* std::unique_ptr */
    std::unique_ptr<A> a = std::make_unique<A>(5);
    a = std::make_unique<A>(7);

    auto b = std::make_unique<A>(11);
    a = std::move(b);
    // a = std::unique_ptr<A>(a);

    /* Unique pointer with arrays */
    int N = 10; /* The size */
    std::unique_ptr<A[]> as = std::make_unique<A[]>(N);
    
    for (auto i = 0; i < N; i++)
        as[i].a_ = i;

    for (auto i = 0; i < N; i++)
        std::cout << as[i].a_ << '\n';

    return 0;
}

std::optional<int> try_divide(int a, int q) {
    if (a % q == 0)
        return a / q;
    else
        return std::nullopt;
}
