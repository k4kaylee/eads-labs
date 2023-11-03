#include <iostream>

template <typename Key, typename Info>
void split_pos(/*const*/ Sequence<Key, Info>& seq, int start_pos, int len1, int len2, int count, // can't be const, we change seq in the function
    Sequence<Key, Info>& seq1, Sequence<Key, Info>& seq2)
{
    const SequenceItem<Key, Info>* currentItem = seq.getHead();
    Sequence<Key, Info> seq0;

    std::cout << "Original Sequence: ";
    seq.print();

    // Move to the starting position
    for (int i = 0; i < start_pos; ++i) {
        if (!currentItem) {
            std::cerr << "Invalid start_pos" << std::endl;
            return;
        }
        seq0.push_front(currentItem->key, currentItem->info);
        currentItem = currentItem->next;
    }

    for (int i = 0; i < count; i++) {

        // Populate seq1
        for (int i = 0; i < len1; ++i) {
            if (!currentItem) {
                break;
            }
            seq1.push_back(currentItem->key, currentItem->info);
            currentItem = currentItem->next;
        }

        // Populate seq2
        for (int i = 0; i < len2; ++i) {
            if (!currentItem) {
                break;
            }
            seq2.push_back(currentItem->key, currentItem->info);
            currentItem = currentItem->next;
        }
    }

    while (currentItem != nullptr) {
        seq0.push_front(currentItem->key, currentItem->info);
        currentItem = currentItem->next;
    }

    seq = seq0;

    
    // Display the resulting sequences
    std::cout << "\n\nSequence: ";
    seq.print();
    std::cout << "\n\nSequence 1: ";
    seq1.print();
    std::cout << "\n\nSequence 2: ";
    seq2.print();
}



template<typename Key, typename Info>
void split_key(Sequence<Key, Info>& seq, const Key& start_key, int start_occ, int len1, int len2, int count,
    Sequence<Key, Info>& seq1, Sequence<Key, Info>& seq2)
{
    const SequenceItem<Key, Info>* currentItem = seq.getHead();
    Sequence<Key, Info> seq0;

    std::cout << "\n\nOriginal Sequence: ";
    seq.print();

    int current_occ = 0;

    while (currentItem && (currentItem->key != start_key || current_occ != start_occ)) {
        seq0.push_back(currentItem->key, currentItem->info);
        currentItem = currentItem->next;

        if (currentItem->key == start_key) {
            current_occ++;
        }
    }

    for (int i = 0; i < len1; ++i) {
        if (!currentItem) {
            break;
        }
        seq1.push_back(currentItem->key, currentItem->info);
        currentItem = currentItem->next;
    }

    for (int i = 0; i < len2; ++i) {
        if (!currentItem) {
            break;
        }
        seq2.push_back(currentItem->key, currentItem->info);
        currentItem = currentItem->next;
    }

    for (int c = 1; c < count; ++c) {
        for (int i = 0; i < len1; ++i) {
            if (!currentItem) {
                break;
            }
            seq1.push_back(currentItem->key, currentItem->info);
            currentItem = currentItem->next;
        }

        for (int i = 0; i < len2; ++i) {
            if (!currentItem) {
                break;
            }
            seq2.push_back(currentItem->key, currentItem->info);
            currentItem = currentItem->next;
        }
    }

    seq = seq0;

    std::cout << "\n\nSequence0: ";
    seq.print();
    std::cout << "\n\nSequence1: ";
    seq1.print();
    std::cout << "\n\nSequence2: ";
    seq2.print();
}

