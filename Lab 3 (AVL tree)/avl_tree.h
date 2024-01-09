#pragma once
#include <utility>
#include <iostream>
#include <vector>
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
		Node(const std::pair<Key, Info>& content) : content(content), left(nullptr), right(nullptr), height(1) {};
		~Node() {
			delete left;
			delete right;
		}

		int getBalanceFactor() const {
			if (!this) {
				return 0;
			}

			int l = left ? left->height : 0;
			int r = right ? right->height : 0;

			return l - r;
		}

		int maxHeight() const {
			int l = left ? left->height : 0;
			int r = right ? right->height : 0;
			return l > r ? l : r;
		}

		void updateHeight() {
			height = 1 + maxHeight();
		}

	};

	void leftRotate(Node*& toRotate) {
		Node* newRoot = toRotate->right;
		toRotate->right = newRoot->left;
		newRoot->left = toRotate;
		toRotate = newRoot;

		toRotate->left->updateHeight();
		toRotate->updateHeight();
	}

	void rightRotate(Node*& toRotate) {
		Node* newRoot = toRotate->left;
		toRotate->left = newRoot->right;
		newRoot->right = toRotate;
		toRotate = newRoot;

		toRotate->right->updateHeight();
		toRotate->updateHeight();
	}

	Node* minValueNode(Node* node){
		while (node && node->left != nullptr)
			node = node->left;

		return node;
	}

	Node* maxValueNode(Node* node) {
		while (node && node->left != nullptr)
			node = node->left;

		return node;
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

	Node* insertNode(Node* current, const std::pair<Key, Info>& content) {
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

		current->updateHeight();
		balanceNode(current);

		return current;
	}

	bool removeNode(Node*& current, const Key& key) {
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

		if(current)
			current->updateHeight();
		balanceNode(current);

		return true;
	}

	Info& searchNode(Node* current, const Key& key) {
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

	void reverseTraversal(const Node* current, std::vector<std::pair<Key, Info>>& result) const {
		if (current) {
			reverseTraversal(current->right, result);

			result.push_back(current->content);

			reverseTraversal(current->left, result);
		}
	}

	void traversal(const Node* current, std::vector<std::pair<Key, Info>>& result) const {
		if (current) {
			traversal(current->left, result);

			result.push_back(current->content);

			traversal(current->right, result);
		}
	}

	Node* copy(const Node* srcNode) {
		if (srcNode == nullptr) {
			return nullptr;
		}
		Node* node = new Node(srcNode->content);
		node->left = copy(srcNode->left);
		node->right = copy(srcNode->right);
		return node;
	}
	
	Node* root;
public:
	avl_tree() {
		root = new Node();
	};

	avl_tree(const avl_tree& src) {
		*this = src;
	};

	~avl_tree() {
		clear();
	};

	void clear() {
		delete root;
		root = nullptr;
	}
	

	avl_tree<Key, Info>& operator=(const avl_tree& src) {
		if (this != &src) {
			clear();
			root = copy(src.root);
		}
		return *this;
	}

	// insert (key, info) pair
	void insert(const std::pair<Key, Info>& content) {
		root = insertNode(root, content);
	}

	// remove given key
	bool remove(const Key& key) {
		return removeNode(root, key);
	}


	// check if given key is present
	bool find(const Key& key) {
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
	
	std::vector<std::pair<Key, Info>> reverseInOrderTraversal() const {
		std::vector<std::pair<Key, Info>> result;
		reverseTraversal(root, result);
		return result;
	}

	std::vector<std::pair<Key, Info>> inOrderTraversal() const {
		std::vector<std::pair<Key, Info>> result;
		traversal(root, result);
		return result;
	}
};




template <typename Key, typename Info>
std::vector<std::pair<Key, Info>> maxinfo_selector(const avl_tree<Key, Info>& tree, unsigned cnt) {
	std::vector<std::pair<Key, Info>> result, descInfo;
	descInfo = tree.reverseInOrderTraversal();

	std::sort(descInfo.begin(), descInfo.end(), [](const auto& a, const auto& b) {
		return a.second > b.second;
	});

	for (unsigned i = 0; i < cnt && i < descInfo.size(); i++)
		result.push_back(descInfo[i]);

	return result;
}
 
avl_tree<std::string, int> count_words(std::istream& is) {
	avl_tree<std::string, int> wordCountTree;

	std::string word;
	while (is >> word) {
		wordCountTree[word]++;
	}

	return wordCountTree;
};