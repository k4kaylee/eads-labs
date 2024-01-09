#include "avl_tree.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>

int main() {
	avl_tree<int, int> tree;

	// Test insertion
	tree.insert({ 1, 10 });
	std::cout << "Tree content: \n";
	tree.print();
	tree.insert({ 2, 15 });
	std::cout << "Tree content: \n";
	tree.print();
	tree.insert({ 11, 0 });
	std::cout << "Tree content: \n";
	tree.print();
	tree.insert({ 12, 100 });
	std::cout << "Tree content: \n";
	tree.print();
	tree.insert({ 5, 5});
	std::cout << "Tree content: \n";
	tree.print();
	tree.insert({ 3, 1 });
	std::cout << "Tree content: \n";
	tree.print();
	tree.insert({ 4, 4 });
	std::cout << "Tree content: \n";
	tree.print();

    std::vector<std::pair<int, int>> result;
    const avl_tree<int, int> const_tree = tree;

    result = maxinfo_selector(const_tree, 10);
    std::cout << "\n\n";
    for (auto i : result)
        std::cout << i.second << " ";

	//std::cout << "\nKey 0: " << (tree.find(0) ? "Found\n" : "Not found\n");
	//std::cout << "Key 12: " << (tree.find(12) ? "Found\n" : "Not found\n");
	//std::cout << "Key 4: " << (tree.find(4) ? "Found\n" : "Not found\n");
	//std::cout << "Key 3: " << (tree.find(3) ? "Found\n" : "Not found\n");
	//std::cout << "Key 5: " << (tree.find(5) ? "Found\n" : "Not found\n");
	//std::cout << "Key 1: " << (tree.find(1) ? "Found\n" : "Not found\n");
	//std::cout << "Key 2: " << (tree.find(2) ? "Found\n" : "Not found\n");

	//std::cout << "\n\nInfo under key '5': " << tree[5];
	//std::cout << "\n\nInfo under key '0': " << tree[0];

	//tree.remove(5);
	//std::cout << "\n\nRemove 5: \n";
	//tree.print();
	//tree.remove(11);
	//std::cout << "Remove 11: \n";
	//tree.print();
	//tree.remove(12);
	//std::cout << "Remove 12: \n";    
	//tree.print();
	//tree.remove(2);
	//std::cout << "Remove 2: \n";
	//tree.print();
	//tree.remove(3);
	//std::cout << "Remove 3: \n";
	//tree.print();
	//tree.remove(4);
	//std::cout << "Remove 4: \n";
	//tree.print();
	//tree.remove(1);
	//std::cout << "Remove 1: \n";
	//tree.print();

    //avl_tree<char, char> tree;

    //// Test insertion
    //tree.insert({ 'i', 'i' });
    //std::cout << "Add i: \n";
    //tree.print();
    //tree.insert({ 'n', 'n' });
    //std::cout << "Add n: \n";
    //tree.print();
    //tree.insert({ 's', 's' });
    //std::cout << "Add s: \n";
    //tree.print();
    //tree.insert({ 't', 't' });
    //std::cout << "Add t: \n";
    //tree.print();
    //tree.remove('i');
    //std::cout << "Remove i: \n";
    //tree.print();
    //tree.remove('t');
    //std::cout << "Remove t: \n";
    //tree.print();
    //tree.insert({ 'u', 'u' });
    //std::cout << "Add u: \n";
    //tree.print();
    //tree.insert({ 't', 't' });
    //std::cout << "Add t: \n";
    //tree.print();
    //tree.insert({ 'e', 'e' });
    //std::cout << "Add e: \n";
    //tree.print();
    //tree.insert({ 'o', 'o' });
    //std::cout << "Add o: \n";
    //tree.print();
    //tree.insert({ 'f', 'f' });
    //std::cout << "Add f: \n";
    //tree.print();
    //tree.insert({ 'c', 'c' });
    //std::cout << "Add c: \n";
    //tree.print();
    //tree.remove('o');
    //std::cout << "Remove o: \n";
    //tree.print();
    //tree.insert({ 'm', 'm' });
    //std::cout << "Add m: \n";
    //tree.print();
    //tree.insert({ 'p', 'p' });
    //std::cout << "Add p: \n";
    //tree.print();
    //tree.remove('u');
    //std::cout << "Remove u: \n";
    //tree.print();
    //tree.remove('t');
    //std::cout << "Remove t: \n";
    //tree.print();
    //tree.insert({ 'e', 'e' });
    //std::cout << "Add e: \n";
    //tree.print();
    //tree.insert({ 'r', 'r' });
    //std::cout << "Add r: \n";
    //tree.print();
    //tree.remove('s');
    //std::cout << "Remove s: \n";
    //tree.print();
    //tree.remove('c');
    //std::cout << "Remove c: \n";
    //tree.print();
    //tree.insert({ 'i', 'i' });
    //std::cout << "Add i: \n";
    //tree.print();
    //tree.insert({ 'e', 'e' });
    //std::cout << "Add e: \n";
    //tree.print();
    //tree.remove('n');
    //std::cout << "Remove n: \n";
    //tree.print();
    //tree.insert({ 'c', 'c' });
    //std::cout << "Add c: \n";
    //tree.print();
    //tree.remove('e');
    //std::cout << "Remove e: \n";
    //tree.print();

    //std::vector<std::pair<char, char>> biggestNodes = maxinfo_selector(tree, 6);
    //for (std::pair<char, char> i : biggestNodes)
    //    std::cout << "\n" << i.first << " " << i.second << "  ";
    //std::cout << std::endl;

    //for (int rep = 0; rep < 5; ++rep) {
    //    std::ifstream is("beagle_voyage.txt");
    //    if (!is) {
    //        std::cout << "Error opening input file.\n";
    //        return 1;
    //    }
    //    std::stringstream tmp;
    //    tmp << is.rdbuf();

    //    auto start_time = std::chrono::high_resolution_clock::now();
    //    avl_tree<std::string, int> wordCountTree = count_words(tmp);
    //    auto end_time = std::chrono::high_resolution_clock::now();

    //    auto time = end_time - start_time;
    //    std::cout << "Elapsed time: " << time / std::chrono::milliseconds(1) << " ms.\n";
    //}

    

	return 0;
}