#ifndef _SNM
#define _SNM
#include<iostream>
#include<unordered_map>
#include<list>
namespace SNM {
template<typename T>
struct Node {
	T x;
	Node<T>* parent;
	virtual int getN(){return 0;};
	virtual void setN(int){};
	virtual int getSize(){return 0;};
	virtual void setSize(int){};
};

template<typename T>
struct ListElement:Node<T> {
	int n;
	int size_tree;
	int getN(){return n;};
	void setN(int x) { n = x;};
	int getSize(){return size_tree;};
	void setSize(int x) { size_tree = x;};
};

template<typename T>
class SetsSystem {
private:
	std::list<Node<T>* > del_list_;
	Node<T>* getNode(Node<T>* x);
	void unionSets(typename std::unordered_map<int,ListElement<T>* >::iterator it_a, typename std::unordered_map<int,ListElement<T>* >::iterator it_b);
	//std::list<ListElement<T> > roots_;
	std::unordered_map<int, ListElement<T>* > roots_;
public:
	Node<T>* addSet(T x, int id);
	void connectAtoB(int a, int b);
	int find(Node<T>* x);
	SetsSystem() {};
	~SetsSystem() {
		for(auto a = del_list_.begin(); a != del_list_.end(); ++a)
			delete *a;
	};
	int getNumOfSets(){return roots_.size();};
	int getNumOfElements(){return del_list.size();};
};
}
#include"SNM.hpp"
#endif