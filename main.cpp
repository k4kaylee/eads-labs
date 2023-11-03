#include <iostream>
#include <cassert>
#include <string>
#include <sstream>
#include "sequence.hpp"
#include "split.hpp"

int main() {
    // Test default constructor
    Sequence<int, std::string> seq1;
    assert(seq1.size() == 0);

    // Test push_front
    seq1.push_front(1, "One");
    std::stringstream ss;
    ss << *seq1.getHead();

    assert(ss.str() == "1 One");
    assert(seq1.size() == 1);

    // Test assignment operator
    Sequence<int, std::string> seq2;
    seq2 = seq1;
    assert(seq1.getHead()->toString() == seq2.getHead()->toString());

    // Test copy constructor
    Sequence<int, std::string>* seq3 = new Sequence<int, std::string>(seq1);
    assert(seq1.getHead()->toString() == seq3->getHead()->toString());

    // Test pop_front
    ss.str("");
    seq1.push_front(2, "Two");
    ss << *seq1.getHead();
    assert(ss.str() == "2 Two"); // double check that we add an element correctly
    seq1.pop_front();
    assert(seq1.getHead()->next == nullptr);

    // Additionally: Test clearAll
    seq1.clearAll();
    assert(seq1.size() == 0);
    assert(seq1.getHead() == nullptr);

    Sequence<int, std::string> seq4, seq5, seq6;
    seq4.push_front(24, "24");
    seq4.push_front(23, "23");
    seq4.push_front(22, "22");
    seq4.push_front(21, "21");
    seq4.push_front(20, "20");
    seq4.push_front(19, "19");
    seq4.push_front(18, "18");
    seq4.push_front(17, "17");
    seq4.push_front(16, "16");
    seq4.push_front(15, "15");
    seq4.push_front(14, "14");
    seq4.push_front(13, "13");
    seq4.push_front(12, "12");
    seq4.push_front(11, "11");
    seq4.push_front(10, "10");
    seq4.push_front(9, "9");
    seq4.push_front(8, "8");
    seq4.push_front(7, "7");
    seq4.push_front(6, "6");
    seq4.push_front(5, "5");
    seq4.push_front(4, "4");
    seq4.push_front(3, "3");
    seq4.push_front(2, "2");
    seq4.push_front(1, "1");
    seq4.push_front(0, "0");


    split_pos(seq4, 2, 2, 3, 4, seq5, seq6);


    Sequence<int, std::string> seq7, seq8, seq9;
    seq7.push_back(0, "0");
    seq7.push_back(1, "1");
    seq7.push_back(2, "2");
    seq7.push_back(3, "3");
    seq7.push_back(4, "4");
    seq7.push_back(5, "5");
    seq7.push_back(6, "6");
    seq7.push_back(4, "4");
    seq7.push_back(8, "8");
    seq7.push_back(9, "9");
    seq7.push_back(4, "4");
    seq7.push_back(11, "11");
    seq7.push_back(12, "12");
    seq7.push_back(2, "2");
    seq7.push_back(14, "14");
    seq7.push_back(15, "15");
    seq7.push_back(11, "11");
    seq7.push_back(17, "17");
    seq7.push_back(23, "23");
    seq7.push_back(19, "19");
    seq7.push_back(20, "20");
    seq7.push_back(21, "21");
    seq7.push_back(22, "22");
    seq7.push_back(23, "23");
    seq7.push_back(24, "24");

    split_key(seq7, 4, 2, 3, 2, 2, seq8, seq9);

    return 0;
}
