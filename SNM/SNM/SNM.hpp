#ifndef _SNM_HPP
#define _SNM_HPP
#include"SNM.h"
using namespace std;
template<typename T>
Node<T>* SetsSystem<T>::addSet(T x, int id) {
	Node<T>* temp_node = new Node<T>;
	temp_node->x = x;
	temp_node->parent = nullptr;

	ListElement<T>* temp_element = new ListElement<T>;
	temp_element->ptr = temp_node;
	temp_element->size_tree = 1;
	temp_element->n = id;

	roots_.push_back(*temp_element);
	temp_element->ptr = nullptr;
	delete temp_element;
	return temp_node;
}

template<typename T>
void SetsSystem<T>::connectAtoB(int a, int b) {
	auto it_a = roots_.begin();
	auto it_b = roots_.begin();
	while(1) {
		if(it_a->n == a)
			break;
		++it_a;
	}
	while(1) {
		if(it_b->n == b)
			break;
		++it_b;
	}
	if(it_a->size_tree > it_b->size_tree) {
		auto temp_ptr = *it_b;
		it_b->ptr = nullptr;
		roots_.erase(it_b);

		temp_ptr.ptr->parent = it_a->ptr;
		it_a->n = temp_ptr.n;
		it_a->size_tree += temp_ptr.size_tree;
	} else {
		auto temp_ptr = *it_a;
		it_a->ptr = nullptr;
		roots_.erase(it_a);

		temp_ptr.ptr->parent = it_b->ptr;
		it_b->size_tree += temp_ptr.size_tree;
	}
}

template<typename T>
Node<T>* SetsSystem<T>::getNode(Node<T>* x) {
	if(x->parent == nullptr)
		return x;
	else
		return getNode(x->parent);
}

template<typename T>
int SetsSystem<T>::find(Node<T>* x) {
	Node<T>* top = getNode(x);
	for(auto i = roots_.begin(); i != roots_.end(); ++i)
		if(i->ptr == top) {
			x->parent = top;
			return i->n;
		}
}
#endif