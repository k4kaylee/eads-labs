#include<iostream>
#include<string>


template <typename Key, typename Info>
class SequenceItem {
public:
	Key key;
	Info info;
	SequenceItem* next;

	SequenceItem(const Key& key, const Info& info, SequenceItem* next = nullptr)
		: key(key), info(info), next(next) {};

	friend std::ostream& operator<<(std::ostream& os, const SequenceItem& si)
	{
		os << si.key << " " << si.info;
		return os;
	}

	std::string toString() const {
		std::stringstream ss;
		ss << this->key << " " << this->info;
		return ss.str();
	}
};

template <typename Key, typename Info>
class Sequence
{
private:
	SequenceItem<Key, Info>* head;
public:
	// implemented as singly linked list
	Sequence() : head(nullptr) {};

	// initialize properly data members 
	// probably as in default constructor *this = src;
	Sequence(const Sequence& src) {
		*this = src;
	}

	~Sequence() {
		this->clearAll();
	};

	Sequence& operator= (const Sequence& src);
	unsigned int size() const; 
	void push_front(const Key& key, const Info& info); // keys are not unique! 
	bool pop_front();

	// and the rest of the interface

	void clearAll();
	const SequenceItem<Key, Info>* getHead() const{
		return this->head;
	};

	void print() const {
		SequenceItem<Key, Info>* current = head;
		while (current) {
			std::cout << "\n" << *current;
			current = current->next;
		}
		std::cout << std::endl;
	}

	void push_back(const Key& key, const Info& info) {
		SequenceItem<Key, Info>* newItem = new SequenceItem<Key, Info>(key, info);

		if (!head) {
			head = newItem;
		}
		else {
			SequenceItem<Key, Info>* current = head;
			while (current->next) {
				current = current->next;
			}

			current->next = newItem;
		}
	}
};

template <typename Key, typename Info>
Sequence<Key, Info>& Sequence<Key, Info>::operator=(const Sequence& sequence) {
	if (this != &sequence) {
		clearAll();

		SequenceItem<Key, Info>* sequenceItem = sequence.head;
		while (sequenceItem) {
			this->push_front(sequenceItem->key, sequenceItem->info);
			sequenceItem = sequenceItem->next;
		}
	}
	return *this;

}


template <typename Key, typename Info>
void Sequence<Key, Info>::push_front(const Key& key, const Info& info) {

	SequenceItem<Key, Info>* newItem = new SequenceItem<Key, Info>(key, info);

	newItem->next = head;
	head = newItem;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::pop_front() {
	if (!head) // empty sequence
		return false;

	SequenceItem<Key, Info>* temp = head;
	head = head->next;
	delete temp;

	return true;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::clearAll() {
	while (head) {
		pop_front();
	}
}

template <typename Key, typename Info>
unsigned int Sequence<Key, Info>::size() const{
	unsigned int size = 0;

	SequenceItem<Key, Info>* temp = this->head;
	while (temp != nullptr) {
		temp = temp->next;
		size++;
	}

	return size;
};
