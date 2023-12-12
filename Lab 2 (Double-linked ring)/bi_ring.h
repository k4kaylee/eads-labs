#pragma once
#include <iostream>
#include <vector>


template <typename Key, typename Info>
class bi_ring {
private:
    template <typename Key, typename Info>
    class Node {
    public:
        Node* next = nullptr;
        Node* prev = nullptr;
        Info info;
        Key key;


        Node() {};
        Node(Info info, Key key) : info(info), key(key) {}
    };
    Node<Key, Info> sentinel;
    int _size;

public:
    class Iterator {
    private:
        friend class bi_ring<Key, Info>;
        Node<Key, Info>* current;
        bi_ring* owner;

    public:
        Iterator(Node<Key, Info>* start, bi_ring* owner) : current(start), owner(owner) {}

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        Iterator& operator--() {
            current = current->prev;
            return *this;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        Key& operator*() const {
            return current->key;
        }

        Info& operator->() const {
            return current->info;
        }

        Key& key() const {
            return current->key;
        }

        Info& info() const {
            return current->info;
        }
    };

    class ConstIterator {
    private:
        friend class bi_ring<Key, Info>;
        const Node<Key, Info>* current;
        const bi_ring* owner;

    public:
        ConstIterator(const Node<Key, Info>* start, const bi_ring* owner) : current(start), owner(owner) {}

        ConstIterator& operator++() {
            current = current->next;
            return *this;
        }

        ConstIterator operator++(int) {
            ConstIterator temp = *this;
            ++(*this);
            return temp;
        }

        ConstIterator& operator--() {
            current = current->prev;
            return *this;
        }

        ConstIterator operator--(int) {
            ConstIterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const ConstIterator& other) const {
            return current == other.current;
        }

        bool operator!=(const ConstIterator& other) const {
            return current != other.current;
        }

        const Key& operator*() const {
            return current->key;
        }

        const Info& operator->() const {
            return current->info;
        }

        const Key& key() const {
            return current->key;
        }

        const Info& info() const {
            return current->info;
        }
    };

    friend std::ostream& operator<<(std::ostream& os, const bi_ring<Key, Info>& ring) {
        if (ring.size() == 0) {
            os << "The ring is empty." << std::endl;
            return os;
        }

        typename bi_ring<Key, Info>::ConstIterator it = ring.cbegin();
        do {
            os << it.key() << " " << it.info() << " ";
            ++it;
        } while (it != ring.cend());

        os << " ";
        return os;
    }

    /**
     * Default constructor for `bi_ring` initializes the sentinel node, making it circular.
     */
    bi_ring() : sentinel(), _size(0) {
        sentinel.next = &sentinel;
        sentinel.prev = &sentinel;
    }

    /**
     * Copy constructor for `bi_ring` creates a new ring by copying elements from the source ring.
     *
     * @param src The source `bi_ring` to copy elements from.
     */
    bi_ring(const bi_ring& src) : bi_ring() {
        const Node<Key, Info>* srcTemp = src.sentinel.next;

        while (srcTemp != &src.sentinel) {
            push_front(srcTemp->key, srcTemp->info);
            srcTemp = srcTemp->next;
        }
    }

    /**
     * Destructor for `bi_ring` deallocates memory by deleting all nodes in the ring.
     */
    ~bi_ring() {
        Node<Key, Info>* temp = sentinel.next;

        while (temp != &sentinel) {
            auto next = temp->next;
            delete temp;
            temp = next;
        }
    }

    /**
     * Copy assignment operator for `bi_ring` assigns a new ring by copying elements from the source ring.
     *
     * @param src The source `bi_ring` to copy elements from.
     * @return Reference to the modified `bi_ring`.
     */
    bi_ring& operator=(const bi_ring& src) {
        const Node<Key, Info>* srcTemp = src.sentinel.prev;

        while (srcTemp != &src.sentinel) {
            push_back(srcTemp->key, srcTemp->info);
            srcTemp = srcTemp->prev;
        }

        return *this;
    }

    int size() const { return _size; }

    bool operator>(const bi_ring& toCompare) {
        return this->_size > toCompare->size();
    }


    /**
     * Inserts a new element with the provided key and info before the specified iterator's position.
     *
     * @param position Iterator pointing on node before which the new node has to be inserted.
     * @param key The key of the new element to insert.
     * @param info The info of the new element to insert.
     * @return Iterator pointing on inserted node.
     */
    Iterator insert(Iterator position, Key key, Info info) {
        Node<Key, Info>* newElement = new Node<Key, Info>(info, key);

        Node<Key, Info>* next = position.current->next;
        newElement->prev = position.current;
        newElement->next = next;
        position.current->next = newElement;
        next->prev = newElement;

        _size++;

        return Iterator(position.current->next, this);
    }

    /**
     * Inserts a new element at the front of the ring.
     *
     * @param key The key of the new element to insert.
     * @param info The info of the new element to insert.
     * @return Iterator pointing on inserted node.
     */
    Iterator push_front(Key key, Info info) {
        return insert(begin(), key, info);
    }

    Iterator push_back(Key key, Info info) {
        return insert(end(), key, info);
    }

    /**
     * Erases the element at the specified iterator's position.
     *
     * @param position Iterator pointing on the node to be erased.
     * @return Iterator pointing on the previous node after the erasure.
     */
    Iterator erase(Iterator position) {
        Iterator newNext = Iterator(position.current->next, this);
        Iterator prev = Iterator(position.current->prev, this);

        delete position.current;
        prev.current->next = newNext.current;
        newNext.current->prev = prev.current;
        _size--;

        return prev;
    }

    /**
     * Erases the element at the front of the ring.
     *
     * @return Iterator pointing on the node after the erasure.
     */
    Iterator pop_front() {
        return erase(begin());
    }

    /**
     * Returns an iterator pointing to the first element in the ring.
     *
     * @return Iterator pointing to the first element.
     */
    Iterator begin() {
        return Iterator(sentinel.next, this);
    }

    /**
     * Returns an iterator pointing to the sentinel node, indicating the end of the ring.
     *
     * @return Iterator pointing to the sentinel node.
     */
    Iterator end() {
        return Iterator(&sentinel, this);
    }

    /**
     * Returns a const iterator pointing to the first element in the ring.
     *
     * @return ConstIterator pointing to the first element.
     */
    ConstIterator cbegin() const {
        return ConstIterator(sentinel.next, this);
    }

    /**
     * Returns a const iterator pointing to the sentinel node, indicating the end of the ring.
     *
     * @return ConstIterator pointing to the sentinel node.
     */
    ConstIterator cend() const {
        return ConstIterator(&sentinel, this);
    }

    /**
     * Prints the key and info of each element in the ring.
     */
    void print() const {
        if (_size == 0) {
            std::cout << "The ring is empty." << std::endl;
            return;
        }

        ConstIterator it = cbegin();
        do {
            std::cout << it.current->key << " " << it.current->info << std::endl;
            ++it;
        } while (it != cend());

        std::cout << "\n\n";
    }
};

template<typename Key, typename Info>
bi_ring<Key, Info> filter(const bi_ring<Key, Info>& source,
    bool (pred)(const Key&)) {
    bi_ring<Key, Info> filteredRing;

    for (auto cit = source.cbegin(); cit != source.cend(); cit++) {
        if (pred(cit.key()))
            filteredRing.push_front(cit.key(), cit.info());
    }

    return filteredRing;
}

template<typename Key, typename Info>
auto findKey(bi_ring<Key, Info>& ring, Key key) {
    for (auto it = ring.begin(); it != ring.end(); ++it) {
        if (*it == key) {
            return it;
        }
    }
    return ring.end();
}

template<typename Key, typename Info>
bi_ring<Key, Info> unique(const bi_ring<Key, Info>& source,
    Info(aggregate)(const Key&, const Info&, const Info&)) {
    bi_ring<Key, Info> uniqueRing;

    for (auto it = source.cbegin(); it != source.cend(); ++it) {
        Key currentKey = it.key();
        Info currentInfo = it.info();

        auto existingKey = findKey(uniqueRing, currentKey);

        if (existingKey == uniqueRing.end()) {
            uniqueRing.push_front(currentKey, currentInfo);
        }
        else {
            Info aggregatedInfo = aggregate(currentKey, existingKey.info(), currentInfo);
            uniqueRing.erase(existingKey);
            uniqueRing.push_front(currentKey, aggregatedInfo);
        }
    }

    return uniqueRing;
}


template<typename Key, typename Info>
Info sumInfo(const Key&, const Info& info1, const Info& info2) {
    return info1 + info2;
}

template<typename Key, typename Info>
bi_ring<Key, Info> join(const bi_ring<Key, Info>& first,
    const bi_ring<Key, Info>& second) {
    bi_ring<Key, Info> merged = first;

    for (auto cit = second.cbegin(); cit != second.cend(); ++cit) {
        merged.push_front(cit.key(), cit.info());
    }

    return unique(merged, sumInfo<Key, Info>);
}

template<typename Key, typename Info>
bi_ring<Key, Info> shuffle(
    const bi_ring<Key, Info>& first, unsigned int fcnt,
    const bi_ring<Key, Info>& second, unsigned int scnt,
    unsigned int reps) {

    bi_ring<Key, Info> shuffled;
    auto cit_first = first.cbegin();
    auto cit_second = second.cbegin();

    for (unsigned int rep = 0; rep < reps; rep++) {
        unsigned int fcn = 0;
        unsigned int scn = 0;

        for (; fcn < fcnt; fcn++) {
            if (cit_first == first.cend()) {
                ++cit_first;
            }
            shuffled.push_back(cit_first.key(), cit_first.info());
            ++cit_first;
        }

        for (; scn < scnt; scn++) {
            if (cit_second == second.cend()) {
                ++cit_second;
            }
            shuffled.push_back(cit_second.key(), cit_second.info());
            ++cit_second;
        }
    }

    return shuffled;
}

//Additional function presented during the lab (#6)
template<typename Key, typename Info>
std::vector<bi_ring<Key, Info>> split(const bi_ring<Key, Info>& source) {
    std::vector<bi_ring<Key, Info>> result;
   
    for (auto cit = source.cbegin(); cit != source.cend();) {

        bi_ring<Key, Info> element;
        auto current_last = element.cend();
        while (cit.key() >= (--current_last).key()) {
            element.push_front(cit.key(), cit.info());
            current_last = element.cend();
            cit++;
        }

         result.push_back(element);
    }
   
    return result;
}
