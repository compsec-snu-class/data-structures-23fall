#include "fheap.hpp"
#include <iostream>

int main() {
   FibonacciHeap<int> heap = {1, 2, 3, 4, 5};
   std::cout << heap.extract_min().has_value() << std::endl;
}
