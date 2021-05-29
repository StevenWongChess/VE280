#ifndef SET_H
#define SET_H

const int MAXELTS = 100;

template<class T>
class Set {
    // OVERVIEW: a mutable set of integers, |set| <= MAXELTS
    const T **elts; // array of elements
    int numElts; // number of elements in array
    int sizeElts; // capacity of array

    int indexOf(const T &v) const;
    // EFFECTS: returns the index of v if it exists in the array,
    //          MAXELTS otherwise.

    void copyFrom(const Set &s);
    // MODIFIES: this
    // EFFECTS: copies s’ contents to this
public:
    Set(int size = MAXELTS); // constructor

    Set(const Set &s); // copy constructor

    Set &operator=(const Set &s); // assignment operator

    ~Set(); // destructor

    void insert(const T *vp);
    // MODIFIES: this
    // EFFECTS: this = this + {v} if room,
    //          throws int MAXELTS otherwise

    const T *remove(const T &v);
    // MODIFIES: this
    // EFFECTS: this = this - {v}

    const T *query(const T &v) const;
    // EFFECTS: returns true if v is in this,
    //          false otherwise

    int size() const;
    // EFFECTS: returns |this|

    void display() const;
    // EFFECTS: prints the elements of this
};

#include "set_impl.h"

#endif
