﻿#pragma once
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

			if (!left && !right)
				return 0;
			else if (!left)
				return -right->height;
			else if (!right)
				return left->height;
			else
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

	void updateHeight(Node*& current) {
		if (current) {
			current->height = 1 + maxHeight(current->left, current->right);
		}
	}

	void leftRotate(Node*& toRotate) {
		Node* newRoot = toRotate->right;
		toRotate->right = newRoot->left;
		newRoot->left = toRotate;
		toRotate = newRoot;

		updateHeight(toRotate->left);
		updateHeight(toRotate);
	}

	void rightRotate(Node*& toRotate) {
		Node* newRoot = toRotate->left;
		toRotate->left = newRoot->right;
		newRoot->right = toRotate;
		toRotate = newRoot;

		updateHeight(toRotate->right);
		updateHeight(toRotate);
	}

	Node* minValueNode(Node* node)
	{
		Node* current = node;

		/* loop down to find the leftmost leaf */
		while (current->left != NULL)
			current = current->left;

		return current;
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
		else if (content.first < current->content.first) {
			current->left = insertNode(current->left, content);
		}
		else {
			current->content.second = content.second;
		}

		current->height = 1 + maxHeight(current->left, current->right);
		int balance = current->getBalanceFactor();

		if (balance > 1 && (!current->left || content.first < current->left->content.first))
			rightRotate(current);

		if (balance < -1 && content.first > current->right->content.first)
			leftRotate(current);


		if (balance > 1 && (!current->left || content.first < current->left->content.first))
		{
			leftRotate(current->left);
			rightRotate(current);
		}

		if (balance < -1 && content.first < current->right->content.first)
		{
			rightRotate(current->right);
			leftRotate(current);
		}
		

		return current;
	}
	void print(Node* current, int spaces) const {
		if (current) {
			spaces += 5;

			print(current->right, spaces);
			

			for (int i = 5; i < spaces; i++) {
				std::cout << " ";
			}

			std::cout << current->content.first << " " << current->getBalanceFactor() << std::endl; // change to balance factor if needed

			print(current->left, spaces);
		}
	}

	bool removeNode(Node*& current, Key key) {
		if (!current) {
			return false;
		}

		if (key > current->content.first) {
			if (removeNode(current->right, key)) {
				current->right = nullptr;
				return true;
			}
			else {
				return false;
			}
		}
		else if (key < current->content.first) {
			if (removeNode(current->left, key)) {
				current->left = nullptr;
				return true;
			}
			else {
				return false;
			}
		}
		else {
			Node* temp = current;
			if (current->left == nullptr) {
				current = current->right;
			}
			else if (current->right == nullptr) {
				current = current->left;
			}
			else {
				Node* minNode = minValueNode(current->right);
				current->content.first = minNode->content.first;
				removeNode(current->right, minNode->content.first);
			}

			delete temp;
			temp = nullptr;

			if (current) {
				current->height = 1 + maxHeight(current->left, current->right);
				int balance = current->getBalanceFactor();

				if (balance > 1 && (!current->left || key < current->left->content.first))
					rightRotate(current);

				if (balance < -1 && key > current->right->content.first)
					leftRotate(current);

				if (balance > 1 && (!current->left || key < current->left->content.first)) {
					leftRotate(current->left);
					rightRotate(current);
				}

				if (balance < -1 && key < current->right->content.first) {
					rightRotate(current->right);
					leftRotate(current);
				}
			}

			return true;
		}
	}

	Info& searchNode(Node* current, Key key) {
		if (!current) {
			// Return a reference to a default-constructed Info object
			static Info defaultInfo; // Assuming Info has a default constructor
			return defaultInfo;
		}

		if (key > current->content.first)
			return searchNode(current->right, key);
		else if (key < current->content.first)
			return searchNode(current->left, key);
		else
			return current->content.second;
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
	bool remove(Key key) {
		return removeNode(root, key);
	}


	// check if given key is present
	bool find(Key key) {
		static Info defaultInfo;
		if (searchNode(root, key) == defaultInfo)
			return false;
		else
			return true;
	}

	// print nicely formatted tree structure
	void print() const{
		if (!root) {
			std::cout << "The tree is empty." << std::endl;
		} else 
			print(root, 0);
	}

	Info& operator[](const Key& key) {
		return searchNode(root, key);
	};

	const Info& operator[](const Key& key) const{
		const Info& result = searchNode(root, key);
		return result;
	}

};