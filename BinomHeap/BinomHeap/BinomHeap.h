template<typename Key_type> struct Node {
	Node* parent_;
	Key_type key_;
	int degree_;
	Node* child_;
	Node* sibling_;
	Node():parent_(nullptr),key_(0),degree_(0),child_(nullptr),sibling_(nullptr){};
	Node(const Key_type& in):parent_(nullptr),key_(in),degree_(0),child_(nullptr),sibling_(nullptr){};
};

template<typename Key_type> class BinomHeap {
private:
	Node<Key_type>* head_;
	int size_;
	template<typename Key_type_0>
	friend Node<Key_type_0>* unionHeaps(BinomHeap<Key_type_0>* bheap_1, BinomHeap<Key_type_0>* bheap_2);
	template<typename Key_type_0>
	friend void linkTrees(Node<Key_type_0>* btree_1, Node<Key_type_0>* btree_2);//connects first to second
	template<typename Key_type_0>
	friend void mergeHeaps(BinomHeap<Key_type_0>* temp_heap,BinomHeap<Key_type_0>* bheap_1,BinomHeap<Key_type_0>* bheap_2);
	BinomHeap* rotate_children();
public:
	BinomHeap():head_(nullptr), size_(0){};
	~BinomHeap(){};
	int size() { return size_;};
	const Key_type& top();
	void push(const Key_type& in);
	void pop();
	void decrease_key(const Key_type& old_key, const Key_type& new_key);
};

#include"BinomHeap.hpp"