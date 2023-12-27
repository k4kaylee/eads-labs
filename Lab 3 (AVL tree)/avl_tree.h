#pragma once
#include <utility>
#include <iostream>
#include <algorithm>


template <typename Key, typename Info>
class avl_tree {
private:
	struct Node {
		std::pair<Key, Info> content;
		Node* left;
		Node* right;
		int height;

		Node() : left(nullptr), right(nullptr), height(0) {};
		Node(std::pair<Key, Info> content) : content(content), left(nullptr), right(nullptr), height(1) {};
		~Node() {
			delete left;
			delete right;
		}

		int getBalanceFactor() const {
			if (!this) {
				return 0;
			}
			return left->height - right->height;
		}
	};

	int maxHeight(Node* first, Node* second) {
		if (!first && !second)
			return 0;
		else if (!first) {
			return second->height;
		}
		else if (!second) {
			return first->height;
		}
		else {
			return first->height > second->height ? first->height : second->height;
		}
	}

	Node* insertNode(Node* current, std::pair<Key, Info> content) {
		if (root->height == 0) {
			root->content = content;
			root->height++;
			return root;
		}

		if (current == nullptr) {
			return new Node(content);
		}

		if (content.first > current->content.first) {
			current->right = insertNode(current->right, content);
		}
		else if (content.first < current->content.first){
			current->left = insertNode(current->left, content);
		}
		else {
			current->content.second = content.second;
		}

		current->height = 1 + maxHeight(current->left, current->right);

		return current;
	}

	void print(Node* current, int spaces) const {
		if (current) {
			spaces += 5;

			print(current->right, spaces);

			for (int i = 5; i < spaces; i++) {
				std::cout << " ";
			}
			std::cout << current->content.first << std::endl;

			print(current->left, spaces);
		}
	}
	
	Node* root;
public:
	avl_tree() {
		root = new Node();
	};
	avl_tree(const avl_tree& src);
	~avl_tree() {
		delete root;
	};

	avl_tree& operator=(const avl_tree& src);

	// insert (key, info) pair
	void insert(std::pair<Key, Info> content) {
		root = insertNode(root, content);
	}

	// remove given key
	// check if given key is present
	// print nicely formatted tree structure
	void print() const{
		if (!root) {
			std::cout << "The tree is empty." << std::endl;
		} else 
			print(root, 0);
	}

	Info& operator[](const Key& key);
	const Info& operator[](const Key& key) const;
	// what else can be useful in such a collection?
};