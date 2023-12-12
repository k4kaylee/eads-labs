#include <iostream>
#include <cassert>
#include <string>
#include "bi_ring.h"
#include "bi_ring_test.h"


int main() {
    run_all_tests();

    bi_ring<std::string, int> ring;
    ring.push_back("otto", 8);
    ring.push_back("sette", 7);
    ring.push_back("sei", 6);
    ring.push_back("cinque", 5);
    ring.push_back("quattro", 4);
    ring.push_back("tre", 3);
    ring.push_back("duo", 2);
    ring.push_back("uno", 1);

    ring.print();

    std::vector<bi_ring<std::string, int>> result = split<std::string, int>(ring);
    for (auto elem : result)
        std::cout << "[ " << elem << " ]" << std::endl << std::endl;
    return 0;
}