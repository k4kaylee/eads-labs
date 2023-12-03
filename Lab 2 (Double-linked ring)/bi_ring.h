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

    bi_ring() : sentinel(), size(0) {
        sentinel.next = &sentinel;
        sentinel.prev = &sentinel;
    }

    bi_ring(const bi_ring& src) : bi_ring() {
        const Node<Key, Info>* srcTemp = src.sentinel.next;


        while (srcTemp != &src.sentinel) {
            push_front(srcTemp->key, srcTemp->info);
            srcTemp = srcTemp->next;
        }
    }

    ~bi_ring() {
        Node<Key, Info>* temp = sentinel.next;

        while (temp != &sentinel) {
            auto next = temp->next;
            delete temp;
            temp = next;
        }
    }

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

    Iterator push_front(Key key, Info info) {
        return insert(begin(), key, info);
    }

    Iterator erase(Iterator position) {
        Iterator newNext = Iterator(position.current->next, this);
        Iterator prev = Iterator(position.current->prev, this);

        delete position.current;
        prev.current->next = newNext.current;
        newNext.current->prev = prev.current;
        size--;
        return prev;
    }

    Iterator pop_front() {
        return erase(begin());
    }

    Iterator begin() {
        return Iterator(sentinel.next, this);
    }

    Iterator end() {
        return Iterator(&sentinel, this);
    }

    ConstIterator cbegin() const {
        return ConstIterator(sentinel.next, this);
    }

    ConstIterator cend() const {
        return ConstIterator(&sentinel, this);
    }

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