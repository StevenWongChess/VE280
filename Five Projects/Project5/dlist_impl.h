#ifndef __DLIST_IMPL_H__
#define __DLIST_IMPL_H__
#include "dlist.h"

class emptyList{

};

template <class T>
bool Dlist<T>::isEmpty() const{
	return this->first == nullptr;
}

template <class T>
void Dlist<T>::insertFront(T *op){
	node *n = new node;
	n->next = first;
	n->prev = nullptr;
	n->op = op;
	this->first = n;
	if(isEmpty()){
		this->last = n;
	}
}
    
template <class T>
void Dlist<T>::insertBack(T *op){
	node *n = new node;
	n->next = nullptr;
	n->prev = last;
	n->op = op;
	this->last = n;
	if(isEmpty()){
		this->first = n;
	}
}

template <class T>
T *Dlist<T>::removeFront(){
	if(isEmpty()){
		throw emptyList();
	}
	this->first = this->first->next;


}
    // MODIFIES this
    // EFFECTS removes and returns first object from non-empty list
    //         throws an instance of emptyList if empty

	T *removeBack();
    // MODIFIES this
    // EFFECTS removes and returns last object from non-empty list
    //         throws an instance of emptyList if empty

template <class T>
Dlist<T>::Dlist(){

}

template <class T>
Dlist<T>::Dlist(const Dlist &l){

}

template <class T>
Dlist<T>::Dlist &operator=(const Dlist &l){

}

template <class T>
Dlist<T>::~Dlist(){

}

void removeAll();
    // EFFECT: called by destructor/operator= to remove and destroy
    //         all list elements

void copyAll(const Dlist &l);
    // EFFECT: called by copy constructor/operator= to copy elements
    //         from a source instance l to this instance
};













#endif