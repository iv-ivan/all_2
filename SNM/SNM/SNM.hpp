#ifndef _SNM_HPP
#define _SNM_HPP
#include"SNM.h"
using namespace std;
template<typename T>
SNM::Node<T>* SNM::SetsSystem<T>::addSet(T x, int id) {
	ListElement<T>* temp_element = new ListElement<T>;
	temp_element->parent = nullptr;
	temp_element->x = x;
	temp_element->size_tree = 1;
	temp_element->n = id;

	roots_.insert(make_pair(id, temp_element));
	del_list_.push_back(temp_element);
	//temp_element->ptr = nullptr;
	//delete temp_element;
	return temp_element;
}

template<typename T>
void SNM::SetsSystem<T>::unionSets(typename std::unordered_map<int,ListElement<T>* >::iterator it_a, typename std::unordered_map<int,ListElement<T>* >::iterator it_b) {
	auto temp_ptr = (it_b->second);
	it_b->second = nullptr;
	roots_.erase(it_b);

	temp_ptr->parent = it_a->second;
	it_a->second->size_tree += temp_ptr->size_tree;
}

template<typename T>
void SNM::SetsSystem<T>::connectAtoB(int a, int b) {
	auto it_a = roots_.find(a);
	auto it_b = roots_.find(b);
	if(it_a->second->size_tree > it_b->second->size_tree) {
		it_a->second->setN(it_b->second->getN());
		unionSets(it_a,it_b);
	} else
		unionSets(it_b,it_a);
}

template<typename T>
SNM::Node<T>* SNM::SetsSystem<T>::getNode(Node<T>* x) {
	if(x->parent == nullptr)
		return x;
	else
		return getNode(x->parent);
}

template<typename T>
int SNM::SetsSystem<T>::find(Node<T>* x) {
	Node<T>* top = getNode(x);
	if(top != x)
		x->parent = top;
	return top->getN();
}
#endif