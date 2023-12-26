#include "avl_tree.h"

int main() {
    avl_tree<int, std::string> tree;

    // Test insertion
    tree.insert({ 1, "One" });
    tree.insert({ 2, "Two" });
    tree.insert({ 12, "Twelve" });
    tree.insert({ 11, "Eleven" });
    tree.insert({ 5, "Five" });
    tree.insert({ 3, "Three" });
    tree.insert({ 4, "Four" });

    // Test print
    std::cout << "Tree content: \n";
    tree.print();

	return 0;
}