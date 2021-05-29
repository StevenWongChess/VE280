#ifndef SKIP_LIST_H
#define SKIP_LIST_H

template<class T>
class SkipList {
    // OVERVIEW: data structure which maintains an ordered sequence
    //           of values without duplication
private:
    struct Node {
        T value;  // the node's value
        Node **forward;  // array of pointers, one pointer for each level,
        // either nullptr or pointing to the next Node on the same level
        // Node();
        Node(T value, int level);  // constructor

        ~Node();  // destructor
    };

    int level;  // level of the skip list
    Node *header;  // header node of the skip list
    void CopyFrom(const SkipList &l);
public:
    SkipList();  // constructor

    SkipList(const SkipList &l);  // copy constructor

    SkipList &operator=(const SkipList &l);  // assignment operator

    ~SkipList();  // destructor

    void insert(T value);
    // MODIFIES: this
    // EFFECTS: inserts "value" into the skip list,
    //          does nothing if the skip list already contains the value

    bool search(T value) const;
    // EFFECTS: returns true if the skip list contains "value",
    //          false otherwise

    void remove(T value);
    // MODIFIES: this
    // EFFECTS: removes "value" from the skip list,
    //          does nothing if the skip list doesn't contain the value

    void display() const;
    // EFFECTS: prints the structure of the skip list
};

#include "skip_list_impl.h"

#endif
