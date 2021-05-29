#ifndef SKIP_LIST_IMPL_H
#define SKIP_LIST_IMPL_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <algorithm>

#include "skip_list.h"

const double P = 0.5;
// the fraction of the nodes with level i pointers also having level i+1 pointers

const int MAX_LEVEL = 25;
// maximum level of a skip list

static int randomLevel();
// EFFECTS: generate a random level for node

// template<class T>
// SkipList<T>::Node::Node(): value(0), forward(nullptr){};

template<class T>
SkipList<T>::Node::Node(T value, int level) : value(value), forward(new Node *[level]()) {};

template<class T>
SkipList<T>::Node::~Node() {
    delete[] forward;
}

template<class T>
SkipList<T>::SkipList(): level(1){
    // TODO: Your implementation here
    this->header = new Node(-1, MAX_LEVEL);
};

template<class T>
void SkipList<T>::CopyFrom(const SkipList &l){
    this->level = l.level;
    this->header = new Node(-1, MAX_LEVEL);
    auto prev = this->header;
    auto it = l.header->forward[0];
    while(it != nullptr){
        auto node = new Node(it->value, level);
        prev->forward[0] = node;
        prev = node;
        it = it->forward[0];
    }
    for(auto i = 1; i < level; i++){
        prev = this->header;
        it = l.header->forward[i];
        while(it != nullptr){
            auto tmp = this->header->forward[i - 1];
            while(tmp->value != it->value){
                tmp = tmp->forward[i - 1];  
            }
            prev->forward[i] = tmp;
            prev = tmp;
            it = it->forward[i];
        }
    }
};

template<class T>
SkipList<T>::SkipList(const SkipList &l) {
    // TODO: Your implementation here
    CopyFrom(l);
}

template<class T>
SkipList<T> &SkipList<T>::operator=(const SkipList &l) {
    // TODO: Your implementation here
    if (this == &l)
        return *this;
    this->~SkipList();
    CopyFrom(l);
    return *this;
}

template<class T>
SkipList<T>::~SkipList() {
    // TODO: Your implementation here
    auto it = this->header;
    while(it != nullptr){
        auto victim = it;
        it = it->forward[0];
        delete victim;
    }
}

template<class T>
void SkipList<T>::insert(T value) {
    // TODO: Your implementation here
    Node *update[MAX_LEVEL];
    for(auto i = 0; i < MAX_LEVEL; i++){
        update[i] = nullptr;
    }
    auto x = this->header;
    for(auto i = this->level - 1; i >= 0; i--){
        while(x->forward[i] != nullptr && x->forward[i]->value < value){
            x = x->forward[i];
        }
        update[i] = x;
    }
    x = x->forward[0];
    if(x == nullptr || x->value != value){
        auto rlevel = randomLevel();    //  
        if(rlevel > this->level){
            for(auto i = this->level; i < rlevel; i++){    //
                update[i] = this->header;
            }
            this->level = rlevel;
        }
        x = new Node(value, rlevel);
        for(auto i = 0; i < rlevel; i++){
            x->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = x;
        }
    }
};

template<class T>
bool SkipList<T>::search(T value) const {
    // TODO: Your implementation here
    auto x = header;
    for(auto i = this->level - 1; i >= 0; i--){
        while(x->forward[i] != nullptr && x->forward[i]->value < value){
            x = x->forward[i];
        }
    }
    x = x->forward[0];
    if(x != nullptr && x->value == value)
        return true;
    return false;
};

template<class T>
void SkipList<T>::remove(T value) {
    // TODO: Your implementation here
    Node *update[MAX_LEVEL];
    for(auto i = 0; i < MAX_LEVEL; i++){
        update[i] = nullptr;
    }
    auto x = this->header;
    for(auto i = this->level - 1; i >= 0; i--){
        while(x->forward[i] != nullptr && x->forward[i]->value < value){
            x = x->forward[i];
        }
        update[i] = x;
    }
    x = x->forward[0];
    if(x != nullptr && x->value == value){
        for(auto i = 0; i < this->level; i++){
            if(update[i]->forward[i] != x)
                break;
            update[i]->forward[i] = x->forward[i];
        }
        delete x;
        while(this->level > 0 && this->header->forward[this->level - 1] == nullptr){
            this->level = this->level - 1;
        }
    }
};

template<class T>
void SkipList<T>::display() const {
    for (int i = level - 1; i >= 0; i--) {
        Node *node = header->forward[i];
        Node *base = header->forward[0];
        std::cout << "[" << i << "] ";
        while (node) {
            while (base->value != node->value) {
                std::ostringstream oss;
                oss << base->value;
                std::cout << std::string(oss.str().length(), '-') << " ";
                base = base->forward[0];
            }
            std::cout << node->value << " ";
            node = node->forward[i];
            base = base->forward[0];
        }
        while (base) {
            std::ostringstream oss;
            oss << base->value;
            std::cout << std::string(oss.str().length(), '-') << " ";
            base = base->forward[0];
        }
        std::cout << std::endl;
    }
};

static inline int randomLevel() {
    int level = 1;
    while ((double) rand() / RAND_MAX < P && level < MAX_LEVEL) {
        level++;
    }
    return level;
};

#endif
