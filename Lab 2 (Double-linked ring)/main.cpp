#include <iostream>
#include <cassert>
#include <string>
#include "bi_ring.h"


int main() {
    bi_ring<int, std::string> ring;

    // Insert elements
    ring.push_front(1, "One");
    ring.push_front(2, "Two");
    ring.push_front(3, "Three");

    ring.print();

    ring.erase(ring.begin());

    ring.print();

    ring.pop_front();

    ring.print();

    ring.pop_front();

    ring.print();

    std::cout << "Test passed successfully!" << std::endl;

    return 0;
}
