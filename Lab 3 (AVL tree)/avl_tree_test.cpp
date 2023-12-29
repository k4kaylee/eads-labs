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
    std::cout << "Tree content: \n";
    tree.print();

    tree.remove(12);
    std::cout << "Tree content: \n";
    tree.print();
    tree.remove(11);
    std::cout << "Tree content: \n";
    tree.print();
    tree.remove(1);
    std::cout << "Tree content: \n";
    tree.print();

    std::cout << "\nKey 0: " << (tree.find(0) ? "Found\n" : "Not found\n");
    std::cout << "Key 12: " << (tree.find(12) ? "Found\n" : "Not found\n");
    std::cout << "Key 4: " << (tree.find(4) ? "Found\n" : "Not found\n");
    std::cout << "Key 3: " << (tree.find(3) ? "Found\n" : "Not found\n");
    std::cout << "Key 5: " << (tree.find(5) ? "Found\n" : "Not found\n");
    std::cout << "Key 1: " << (tree.find(1) ? "Found\n" : "Not found\n");
    std::cout << "Key 2: " << (tree.find(2) ? "Found\n" : "Not found\n");

    std::cout << "\n\nInfo under key '5': " << tree[5];
    std::cout << "\n\nInfo under key '0': " << tree[0];
	return 0;
}