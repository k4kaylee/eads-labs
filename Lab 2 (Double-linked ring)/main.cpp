    #include <iostream>
    #include <cassert>
    #include <string>
    #include "bi_ring.h"


bool isKey3(const int& key) {
    return key == 3;
}

template<typename Key, typename Info>
Info writeWithDash(const Key&, const Info& info1, const Info& info2) {
    return info1 + "-" + info2;
}

    int main() {
        bi_ring<int, std::string> ring, ring1;

        // Insert elements
        ring.push_front(1, "One");
        ring.push_front(2, "Two");
        ring.push_front(3, "Three");

        ring.print();

        ring1 = ring; 

        ring1.erase(ring.begin());

        ring1.print();

        bi_ring<int, std::string> ring2 = bi_ring<int, std::string>(ring1);
        ring2.pop_front();

        ring2.print();

        ring2.pop_front();

        ring2.print();

        std::cout << "Test passed successfully!" << std::endl;

        ring.push_front(3, "Three");
        ring.push_front(3, "Three");
        ring.push_front(3, "Three");

        bi_ring<int, std::string> filteredRing = filter(ring, isKey3);

        filteredRing.print();

        bi_ring<int, std::string> uniqueRing = unique(ring, writeWithDash);

        ring.print();
        uniqueRing.print();

        bi_ring<int, int> ring4, ring5, merged;
        ring4.push_front(5, 5);
        ring4.push_front(4, 5);
        ring4.push_front(6, 6);

        ring5.push_front(5, 5);
        ring5.push_front(6, 6);

        merged = join(ring4, ring5);
        merged.print();



        return 0;
    }
