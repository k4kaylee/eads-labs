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

		while (current && current->left != nullptr)
			current = current->left;

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

	void balanceNode(Node*& current) {
		if (!current) {
			return;
		}

		int balance = current->getBalanceFactor();

		// Left Left Case
		if (balance > 1 && current->left->getBalanceFactor() >= 0) {
			rightRotate(current);
		}

		// Left Right Case
		if (balance > 1 && current->left->getBalanceFactor() < 0) {
			leftRotate(current->left);
			rightRotate(current);
		}

		// Right Right Case
		if (balance < -1 && current->right->getBalanceFactor() <= 0) {
			leftRotate(current);
		}

		// Right Left Case
		if (balance < -1 && current->right->getBalanceFactor() > 0) {
			rightRotate(current->right);
			leftRotate(current);
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
		else if (content.first < current->content.first) {
			current->left = insertNode(current->left, content);
		}
		else {
			current->content.second = content.second;
		}

		updateHeight(current);
		balanceNode(current);

		return current;
	}

	bool removeNode(Node*& current, Key key) {
		if (!current) {
			return false;
		}

		if (key > current->content.first) {
			removeNode(current->right, key);
		}
		else if (key < current->content.first) {
			removeNode(current->left, key);
		}
		else {
			Node* temp = current;
			if (current->left != nullptr && current->right != nullptr) {
				Node* minNode = minValueNode(current->right);
				current->content = minNode->content;
				removeNode(current->right, minNode->content.first);
			}
			else if (current->left == nullptr) {
				current = current->right;
				temp->right = nullptr;
			}
			else if (current->right == nullptr) {
				current = current->left;
				temp->left = nullptr;
			}
		}

		updateHeight(current);
		balanceNode(current);

		return true;
	}

	Info& searchNode(Node* current, Key key) {
		if (!current) {
			static Info defaultInfo; 
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

	avl_tree(const avl_tree& src) {
		root = nullptr;
		if (src.root) {
			root = new Node(src.root->content);
			root->left = src.root->left ? new Node(*(src.root->left)) : nullptr;
			root->right = src.root->right ? new Node(*(src.root->right)) : nullptr;
		}
	};

	~avl_tree() {
		delete root;
	};
	

	avl_tree<Key, Info>& operator=(const avl_tree& src) {
		if (this != &src) {
			delete root;

			root = nullptr;
			if (src.root) {
				root = new Node(src.root->content);
				root->left = src.root->left ? new Node(*(src.root->left)) : nullptr;
				root->right = src.root->right ? new Node(*(src.root->right)) : nullptr;
			}
		}
		return *this;
	}

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