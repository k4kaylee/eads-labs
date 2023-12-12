#include "bi_ring.h"
#include "bi_ring_test.h"
#include <string>
#include <cassert>
#include <iostream>
#include <sstream>

void test_ring() {
	bi_ring<int, std::string> ring, ring1;
	std::stringstream ss;
	ss << ring;	
	assert(ring.size() == 0);
	assert(ss.str() == "The ring is empty.\n");
	assert(ring.begin() == ring.end());
}


void test_push_pop() {
	bi_ring<int, std::string> ring;
	std::stringstream ss;
	ring.push_front(2, "Two");
	ss << ring;
	assert(ss.str() == "2 Two  ");
	ring.push_front(3, "Three");
	ring.push_back(1, "One");
	ss.str("");
	ss << ring;
	assert(ss.str() == "1 One 2 Two 3 Three  ");

	ring.insert(ring.begin()++, 2, "Two-copy");
	ss.str("");
	ss << ring;
	assert(ss.str() == "1 One 2 Two-copy 2 Two 3 Three  ");
	ring.pop_front();
	ring.erase(ring.begin()++);
	ss.str("");
	ss << ring;
	assert(ss.str() == "2 Two 3 Three  ");
}

void test_copy() {
	bi_ring<int, std::string> ring, ring1;
	ring.push_front(1, "One");
	ring.push_front(2, "Two");
	ring.push_front(3, "Three");

	ring1 = ring; 
	std::stringstream ss, ss1;
	ss << ring;
	ss1 << ring1;
	assert(ss.str() == ss1.str());
}

bool isKey3(const int& key) {
	return key == 3;
}

void test_filter() {
	bi_ring<int, std::string> ring;
	std::stringstream ss;

	ring.push_front(3, "Three");
	ring.push_front(3, "Three");
	ring.push_front(3, "Three");
	ring.push_front(2, "Two");
	ring.push_front(1, "One");
	
	bi_ring<int, std::string> filtered_ring = filter(ring, isKey3);
	ss << filtered_ring;
	assert(ss.str() == "3 Three 3 Three 3 Three  ");
}

template<typename Key, typename Info>
Info writeWithDash(const Key&, const Info& info1, const Info& info2) {
	return info1 + "-" + info2;
}

void test_unique() {
	bi_ring<int, std::string> ring;
	std::stringstream ss;
	
	ring.push_front(3, "Three");
	ring.push_front(3, "Three");
	ring.push_front(3, "Three");
	ring.push_front(2, "Two");
	ring.push_front(1, "One");

	bi_ring<int, std::string> unique_ring = unique(ring, writeWithDash);
	ss << unique_ring;
	assert(ss.str() == "2 Two 3 Three-Three-Three 1 One  ");
}

void test_join() {
	bi_ring<int, int> ring4, ring5, merged;
	std::stringstream ss;

	ring4.push_front(5, 5);
	ring4.push_front(4, 5);
	ring4.push_front(6, 6);

	ring5.push_front(5, 5);
	ring5.push_front(6, 6);

	merged = join(ring4, ring5);
	ss << merged;

	assert(ss.str() == "4 5 6 12 5 10  ");
	
}

void test_shuffle() {
	bi_ring<int, std::string> ring6, ring7;
	std::stringstream ss;

	ring6.push_back(4, "quattro");
	ring6.push_back(3, "tre");
	ring6.push_back(2, "due");
	ring6.push_back(1, "uno");

	ring7.push_back(5, "bes");
	ring7.push_back(4, "dort");
	ring7.push_back(3, "uc");
	ring7.push_back(2, "iki");
	ring7.push_back(1, "bir");

	ss << shuffle(ring6, 1, ring7, 2, 3);
	assert(ss.str() == "1 bir 5 bes 3 tre 4 dort 3 uc 2 due 2 iki 1 bir 1 uno  ");
}

void run_all_tests() {
	test_ring();
	test_push_pop();
	test_copy();
	test_filter();
	test_unique();
	test_join();
	test_shuffle();

	std::cout << "Test passed successfully!" << std::endl;
}