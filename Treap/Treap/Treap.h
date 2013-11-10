//----------dekart tree------------
//-------Ivan Ivashkovskiy---------
#ifndef _TREAP_H
#define _TREAP_H
#include<vector>
#include<iostream>
namespace my_treap {
	template<typename type_key, typename type_prior>
	class Treap;

	template<typename type_key, typename type_prior>
	class Node {
	public:
		Node* getParent();
		Node* getL();
		Node* getR();
		void setParent(Node*);
		void setL(Node*);
		void setR(Node*);
		const type_key& getKey();
		const type_prior& getPrior();
		Node(const type_key&, const type_prior&);
		Node(const Node&);
		~Node();
	private:
		Node* parent_;
		Node* l_child_;
		Node* r_child_;
		std::pair<type_key, type_prior> key_prior_;
	};

	template<typename type_key, typename type_prior>
	class Treap {//binary search tree - left < current, right >= current
	public:
		void insert(const type_key&, const type_prior&);
		const type_prior& search(const type_key&) const;
		void erase(const type_key&);
		void unionWith(Treap&);
		Treap();
		void orderBuild(const std::vector<std::pair<type_key, type_prior> >&, const int& index_start, const int& ind_end);
		~Treap();
	private:
		Node<type_key, type_prior>* deepSearch(Node<type_key, type_prior>*, const type_key&) const;
		template<typename type_key, typename type_prior>
		friend std::ostream& operator << (std::ostream&, Treap<type_key, type_prior>&);
		template<typename type_key, typename type_prior>
		friend Node<type_key, type_prior>* unionTreaps(Node<type_key, type_prior>* a,Node<type_key, type_prior>* b);
		std::pair<Node<type_key, type_prior>*, char> searchPlace(Node<type_key, type_prior>*, const type_key&, const type_prior&, char);
		void deleteNode(Node<type_key, type_prior>*);
		Node<type_key, type_prior>* root_;//least at the root
		void orderInsert(Node<type_key,type_prior>** cur_node_ptr, const type_key& key, const type_prior& prior);
	};
	#include"Treap.hpp"
}
#endif