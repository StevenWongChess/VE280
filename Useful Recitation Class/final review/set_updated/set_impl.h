#ifndef SET_IMPL_H
#define SET_IMPL_H

#include <iostream>

template<class T>
int Set<T>::indexOf(const T &v) const {
    for (int i = 0; i < numElts; i++) {
        if (*elts[i] == v) return i;
    }
    return MAXELTS;
}

template<class T>
void Set<T>::copyFrom(const Set &s) {
    for (int i = 0; i < numElts; i++) {
        delete elts[i];
    }
    if (s.sizeElts != sizeElts) {
        delete[] elts;
        sizeElts = s.sizeElts;
        elts = new const T *[sizeElts];
    }
    for (int i = 0; i < s.sizeElts; i++) {
        if (i < s.numElts) {
            elts[i] = new const T(*s.elts[i]);
        } else {
            elts[i] = s.elts[i];
        }
    }
    numElts = s.numElts;
}

template<class T>
Set<T>::Set(int size) :
        elts(new const T *[size]),
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
    for (int i = 0; i < numElts; i++) {
        delete elts[i];
    }
    delete[] elts;
}

template<class T>
void Set<T>::insert(const T *vp) {
    if (indexOf(*vp) == MAXELTS) {
        if (numElts == MAXELTS) throw MAXELTS;
        int cand = numElts - 1;
        while ((cand >= 0) && *elts[cand] > *vp) {
            elts[cand + 1] = elts[cand];
            cand--;
        }
        elts[cand + 1] = vp;
        numElts++;
    } else {
        delete vp;
    }
}

template<class T>
const T *Set<T>::remove(const T &v) {
    int victim = indexOf(v);
    if (victim != MAXELTS) {
        const T *vp = elts[victim];
        numElts--;
        while (victim < numElts) {
            elts[victim] = elts[victim + 1];
            victim++;
        }
        return vp;
    } else {
        return nullptr;
    }
}

template<class T>
const T *Set<T>::query(const T &v) const {
    int i = indexOf(v);
    if (i != MAXELTS) {
        return elts[i];
    } else {
        return nullptr;
    }
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
            std::cout << *elts[i] << ", ";
        }
        std::cout << *elts[numElts - 1] << " }";
    } else {
        std::cout << "{ }";
    }
}

#endif
