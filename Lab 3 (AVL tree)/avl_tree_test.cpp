#include "avl_tree.h"

int main() {
    avl_tree<int, std::string> tree;

    // Test insertion
    tree.insert({ 1, "One" });
    std::cout << "Tree content: \n";
    tree.print();
    tree.insert({ 2, "Two" });
    std::cout << "Tree content: \n";
    tree.print();
    tree.insert({ 11, "Eleven" });
    std::cout << "Tree content: \n";
    tree.print();
    tree.insert({ 12, "Twelve" });
    std::cout << "Tree content: \n";
    tree.print();
    tree.insert({ 5, "Five" });
    std::cout << "Tree content: \n";
    tree.print();
    tree.insert({ 3, "Three" });
    std::cout << "Tree content: \n";
    tree.print();
    tree.insert({ 4, "Four" });

    // Test print
    std::cout << "Tree content: \n";
    tree.print();

	return 0;
}