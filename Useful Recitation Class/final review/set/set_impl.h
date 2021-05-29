#ifndef SET_IMPL_H
#define SET_IMPL_H

#include <iostream>

template<class T>
int Set<T>::indexOf(T v) const {
    for (int i = 0; i < numElts; i++) {
        if (elts[i] == v) return i;
    }
    return MAXELTS;
}

template<class T>
void Set<T>::copyFrom(const Set &s) {
    if (s.sizeElts != sizeElts) {
        delete[] elts;
        sizeElts = s.sizeElts;
        elts = new T[sizeElts];
    }
    for (int i = 0; i < s.sizeElts; i++) {
        elts[i] = s.elts[i];
    }
    numElts = s.numElts;
}

template<class T>
Set<T>::Set(int size) :
        elts(new T[size]),
        numElts(0),
        sizeElts(size) {
}

template<class T>
Set<T>::Set(const Set &s) :
        elts(nullptr),
        numElts(0),
        sizeElts(0) {
    copyFrom(s);
}

template<class T>
Set<T> &Set<T>::operator=(const Set &s) {
    if (this != &s) {
        copyFrom(s);
    }
    return *this;
}

template<class T>
Set<T>::~Set() {
    delete[] elts;
}

template<class T>
void Set<T>::insert(T v) {
    if (indexOf(v) == MAXELTS) {
        if (numElts == MAXELTS) throw MAXELTS;
        int cand = numElts - 1;
        while ((cand >= 0) && elts[cand] > v) {
            elts[cand + 1] = elts[cand];
            cand--;
        }
        elts[cand + 1] = v;
        numElts++;
    }
}

template<class T>
void Set<T>::remove(T v) {
    int victim = indexOf(v);
    if (victim != MAXELTS) {
        numElts--;
        while (victim < numElts) {
            elts[victim] = elts[victim + 1];
            victim++;
        }
    }
}

template<class T>
bool Set<T>::query(T v) const {
    return (indexOf(v) != MAXELTS);
}

template<class T>
int Set<T>::size() const {
    return numElts;
}

template<class T>
void Set<T>::display() const {
    if (numElts) {
        std::cout << "{ ";
        for (int i = 0; i < numElts - 1; i++) {
            std::cout << elts[i] << ", ";
        }
        std::cout << elts[numElts - 1] << " }";
    } else {
        std::cout << "{ }";
    }
}

#endif
