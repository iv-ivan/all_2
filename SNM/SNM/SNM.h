#ifndef _SNM
#define _SNM
#include<iostream>
#include<list>
template<typename T>
struct Node {
	T x;
	Node<T>* parent;
};

template<typename T>
struct ListElement {
	int size_tree;
	int n;
	Node<T>* ptr;
};

template<typename T>
class SetsSystem {
private:
	Node<T>* getNode(Node<T>* x);
	std::list<ListElement<T> > roots_;
public:
	Node<T>* addSet(T x, int id);
	void connectAtoB(int a, int b);
	int find(Node<T>* x);
	SetsSystem() {};
	~SetsSystem() {};
};
#include"SNM.hpp"
#endif