#ifndef __DLIST_IMPL_H__
#define __DLIST_IMPL_H__
#include <iostream>
#include "dlist.h"

template <class T>
void Dlist<T>::printDlist(){
	node *it = this->first;
	while(it){
		std::cout << *it->op << " ";
		it = it->next;
	}
	std::cout << std::endl;
}

template <class T>
bool Dlist<T>::isEmpty() const{
	return this->first == nullptr;
}

template <class T>
void Dlist<T>::insertFront(T *op){
	node *n = new node;
	n->next = this->first;
	n->prev = nullptr;
	n->op = op;
	if(isEmpty()){
		this->last = n;
	}
	else{
		this->first->prev = n;
	}
	this->first = n;
}
    
template <class T>
void Dlist<T>::insertBack(T *op){
	node *n = new node;
	n->next = nullptr;
	n->prev = this->last;
	n->op = op;
	if(isEmpty()){
		this->first = n;
	}
	else{
		this->last->next = n;
	}
	this->last = n;
}

template <class T>
T *Dlist<T>::removeFront(){
	if(isEmpty()){
		throw emptyList();
	}
	node *victim = this->first;
	T *tmp = victim->op;
	this->first = this->first->next;
	if(!this->first){
		this->last = nullptr;
	}
	else{
		this->first->prev = nullptr;
	}
	delete victim;
	return tmp;
}

template <class T>
T *Dlist<T>::removeBack(){
	if(isEmpty()){
		throw emptyList();
	}
	node *victim = this->last;
	T *tmp = victim->op;
	this->last = this->last->prev;
	if (!this->last){
		this->first = nullptr;
	}
	else{
		this->last->next = nullptr;
	}
	delete victim;
	return tmp;
}

template <class T>
Dlist<T>::Dlist(): first(nullptr), last(nullptr){

}

template <class T>
Dlist<T>::Dlist(const Dlist<T> &l){
	// removeAll();
	this->first = this->last = nullptr;
	copyAll(l);
}

template <class T>
Dlist<T> & Dlist<T>::operator=(const Dlist<T> &l){
	removeAll();
	copyAll(l);
	return *this;
}

template <class T>
Dlist<T>::~Dlist(){
	removeAll();
}

template <class T>
void Dlist<T>::removeAll(){
	node *it = this->first;
	while(it){
		delete it->op;
		node *victim = it;
		it = it->next;
		delete victim;
	}
	this->first = this->last = nullptr;
}

template <class T>
void Dlist<T>::copyAll(const Dlist<T> &l){
	removeAll();
	if(!l.isEmpty()){
		node *it = l.first;
		while(it){
			T *op_ = new T(*it->op);
			insertBack(op_);
			it = it->next;
		}
	}
}

#endif