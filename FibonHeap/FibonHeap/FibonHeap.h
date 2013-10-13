template<typename Key_type> struct Node {
	Node* parent_;
	Key_type key_;
	int degree_;
	bool mark_;
	Node* child_;
	Node* left_;
	Node* right_;
	Node():mark_(0),parent_(nullptr),key_(0),degree_(0),child_(nullptr),left_(nullptr),right_(nullptr){};
	Node(const Key_type& in):mark_(0),parent_(nullptr),key_(in),degree_(0),child_(nullptr),left_(nullptr),right_(nullptr){};
};

template<typename Key_type> class FibonHeap {
private:
	Node<Key_type>* min_;
	int size_;
	int size_root_;
	void consolidate();
	void link(Node<Key_type>* node_1, Node<Key_type>* node_2);
	void deleteTree(Node<Key_type>* current_node) {
		if(current_node == nullptr)
			return;
		if(current_node->child_ != nullptr)
		{
			deleteTree(current_node->child_);
			current_node->child_ = nullptr;
		}
		if(current_node->left_ != current_node) {
			current_node->left_->right_ = current_node->right_;
			current_node->right_->left_ = current_node->left_;
			Node<Key_type>* temp = current_node->right_;
			delete current_node;
			deleteTree(temp);
		} else
			delete current_node;	
	}
	void cut(Node<Key_type>* node, Node<Key_type>* node_parent);
	void cascadingCut(Node<Key_type>* node);
public:
	void unionHeaps(FibonHeap<Key_type>* fheap);
	FibonHeap():min_(nullptr), size_(0),size_root_(0){};
	~FibonHeap() {
		deleteTree(min_);
		min_ = nullptr;
		size_ = 0;
		size_root_ = 0;
	};
	int size() { return size_;};
	const Key_type top();
	Node<Key_type>* push(const Key_type& in);
	void pop();
	void decreaseKey(Node<Key_type>* node, const Key_type& new_key);
	void deleteKey(Node<Key_type>* node);
};

#include"FibonHeap.hpp"