#pragma once

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
    int size;

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
    };

    /**
 * Default constructor for `bi_ring` initializes the sentinel node, making it circular.
 */
    bi_ring() : sentinel(), size(0) {
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
        const Node<Key, Info>* srcTemp = src.sentinel.next;

        while (srcTemp != &src.sentinel) {
            push_front(srcTemp->key, srcTemp->info);
            srcTemp = srcTemp->next;
        }

        return *this;
    }

    bool operator>(const bi_ring& toCompare) {
        return this->size > toCompare->size();
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

        size++;

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
        size--;

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
        if (size == 0) {
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
        if (pred(*cit))
            filteredRing.push_front(*cit, cit.operator->());
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
        Key currentKey = *it;
        Info currentInfo = it.operator->();

        auto existingKey = findKey(uniqueRing, currentKey);

        if (existingKey == uniqueRing.end()) {
            uniqueRing.push_front(currentKey, currentInfo);
        }
        else {
            Info aggregatedInfo = aggregate(currentKey, existingKey.operator->(), currentInfo);
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
        merged.push_front(*cit, cit.operator->());
    }

    merged.print();
    return unique(merged, sumInfo<Key, Info>);
}

