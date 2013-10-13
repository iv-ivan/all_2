#ifndef _FIBONHEAP_HPP
#define _FIBONHEAP_HPP
#include<vector>
template<typename Key_type>
const Key_type FibonHeap<Key_type>::top() {
	if(min_ == nullptr)
		return 0;
	return min_->key_;
}
/*
template<typename Key_type>
void linkTrees(Node<Key_type>* btree_1, Node<Key_type>* btree_2) {
	btree_1->parent_ = btree_2;
	btree_1->sibling_ = btree_2->child_;
	btree_2->child_ = btree_1;
	++(btree_2->degree_);
}
*/
template<typename Key_type>
void FibonHeap<Key_type>::unionHeaps(FibonHeap<Key_type>* fheap) {
	if(fheap->min_ == nullptr) {
		return;
	} else {
		if(min_ == nullptr) {
			min_ = fheap->min_;
			size_ = fheap->size;
			size_root_ = fheap->size_root_;
			fheap = nullptr;
			return;
		} else {
			fheap_->left_->right = min_->right_;
			min_->right_->left_ = fheap_->left;
			fheap->min_->left_ = min_;
			min_->right_ = fheap->min_;
			if(min_->key > fheap->min_->key_)
				min_ = fheap->min_;
			fheap = nullptr;
		}
	}
	size_ += fheap->size_;
	size_root_ += fheap->size_root_;
}

template<typename Key_type>
Node<Key_type>* FibonHeap<Key_type>::push(const Key_type& in) {
	Node<Key_type>* temp_node = new Node<Key_type>;
	temp_node->key_ = in;
	if(min_ == nullptr) {
		temp_node->left_ = temp_node;
		temp_node->right_ = temp_node;
		min_ = temp_node;
	} else {
		temp_node->right_ = min_->right_;
		temp_node->left_ = min_;
		min_->right_->left_ = temp_node;
		min_->right_ = temp_node;
		if(min_->key_ > temp_node->key_)
			min_ = temp_node;
	}
	++size_;
	++size_root_;
	return temp_node;
}

template<typename Key_type>
void FibonHeap<Key_type>::consolidate() {
	std::vector<Node<Key_type>*> arr_nodes(size_, nullptr);
	Node<Key_type>* cur_node = min_;
	int cur_size = size_root_;
	for(int i = 0; i < cur_size; ++i) {
		Node<Key_type>* temp_node_1 = cur_node;
		int d = temp_node_1->degree_;
		while(arr_nodes[d] != nullptr) {
			Node<Key_type>* temp_node_2 = arr_nodes[d];
			if(temp_node_1->key_ > temp_node_2->key_) {
				Node<Key_type>* ptr = temp_node_1->right_;
				temp_node_1->right_ = temp_node_2->right_;
				temp_node_2->right_->left_ = temp_node_1;
				temp_node_2->right_ = ptr;
				ptr->left_ = temp_node_2;

				ptr = temp_node_1->left_;
				temp_node_1->left_ = temp_node_2->left_;
				temp_node_2->left_->right_ = temp_node_1;
				temp_node_2->left_ = ptr;
				ptr->right_ = temp_node_2;

				ptr = temp_node_1;
				temp_node_1 = temp_node_2;
				temp_node_2 = ptr;
				cur_node = temp_node_1;
			}
			link(temp_node_2, temp_node_1);
			--size_root_;
			//--size_;
			arr_nodes[d] = nullptr;
			++d;
		}
		arr_nodes[d] = temp_node_1;
		min_ = temp_node_1;
		cur_node = cur_node->right_;
	}
	cur_node = min_;
	for(int i = 0; i < size_root_; ++i) {
		if(cur_node->key_ < min_->key_)
			min_ = cur_node;
		cur_node = cur_node->right_;
	}
}

template<typename Key_type>
void FibonHeap<Key_type>::link(Node<Key_type>* node_1, Node<Key_type>* node_2) {
	node_1->left_->right_ = node_1->right_;
	node_1->right_->left_ = node_1->left_;
	node_1->parent_ = node_2;
	if(node_2->child_ == nullptr) {
		node_2->child_ = node_1;
		node_1->right_ = node_1;
		node_1->left_ = node_1;
	} else {
		node_2->child_->right_->left_ = node_1;
		node_1->right_ = node_2->child_->right_;
		node_2->child_->right_ = node_1;
		node_1->left_ = node_2->child_;
	}
	++(node_2->degree_);
	node_1->mark_ = 0;
}

template<typename Key_type>
void FibonHeap<Key_type>::pop() {
	if(min_ == nullptr)
		return;
	Node<Key_type>* temp_ptr = min_;
	Node<Key_type>* temp_child = temp_ptr->child_;
	if(temp_child != nullptr)
		while(1) {
			Node<Key_type>* next_child = temp_child->right_;
			temp_child->parent_ = nullptr;
			temp_child->right_ = min_->right_;
			temp_child->left_ = min_;
			min_->right_->left_ = temp_child;
			min_->right_ = temp_child;
			++size_root_;
			if(next_child == min_->child_)
				break;
			else
				temp_child = next_child;
		}
	Node<Key_type>* temp_min = min_->right_;
	if(temp_min == min_) {
		delete min_;
		min_ = nullptr;
		--size_;
		--size_root_;
		return;
	}
	min_->left_->right_ = min_->right_;
	min_->right_->left_ = min_->left_;
	delete min_;
	min_ = temp_min;
	--size_;
	--size_root_;
	consolidate();
}

template<typename Key_type>
void FibonHeap<Key_type>::decreaseKey(Node<Key_type>* node, const Key_type& new_key) {
	if(new_key > node->key_)
		return;
	node->key_ = new_key;
	Node<Key_type>* temp_node = node;
	Node<Key_type>* temp_node_parent = node->parent_;
	if(temp_node_parent != nullptr && temp_node->key_ < temp_node_parent->key_) {
		cut(temp_node, temp_node_parent);
		cascadingCut(temp_node_parent);
	}
	if(temp_node->key_ < min_->key_)
		min_ = temp_node;
}

template<typename Key_type>
void FibonHeap<Key_type>::cut(Node<Key_type>* node, Node<Key_type>* node_parent) {
	--(node_parent->degree_);
	node_parent->child_ = node->right_;
	if(node_parent->child_ == node)
		node_parent->child_ = nullptr;
	node->right_->left_ = node->left_;
	node->left_->right_ = node->right_;
	node->parent_ = nullptr;
	++size_root_;

	min_->left_->right_ = node;
	node->left_ = min_->left_;
	node->right_ = min_;
	min_->left_ = node;
	node->mark_ = 0;
}

template<typename Key_type>
void FibonHeap<Key_type>::cascadingCut(Node<Key_type>* node) {
	Node<Key_type>* parent = node->parent_;
	if(parent != nullptr)
		if(node->mark_ == 0)
			node->mark_ = 1;
		else {
			cut(node, parent);
			cascadingCut(parent);
		}
}

template<typename Key_type>
void FibonHeap<Key_type>::deleteKey(Node<Key_type>* node) {
	decreaseKey(node, Key_type(std::numeric_limits<int>:min));
	pop();
}
#endif