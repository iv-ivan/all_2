#ifndef _BINOMHEAP_HPP
#define _BINOMHEAP_HPP
template<typename Key_type>
const Key_type BinomHeap<Key_type>::top() {
	if(head_ == nullptr)
		return 0;
	Node<Key_type>* current_node = head_;
	Node<Key_type>* ptr_min = current_node;
	Key_type min = current_node->key_;
	while(current_node != nullptr) {
		if(current_node->key_ < min) {
			min = current_node->key_;
			ptr_min = current_node;
		}
		current_node = current_node->sibling_;
	}
	return ptr_min->key_;
}

template<typename Key_type>
void linkTrees(Node<Key_type>* btree_1, Node<Key_type>* btree_2) {
	btree_1->parent_ = btree_2;
	btree_1->sibling_ = btree_2->child_;
	btree_2->child_ = btree_1;
	++(btree_2->degree_);
}

template<typename Key_type>
void BinomHeap<Key_type>::unionHeaps(BinomHeap<Key_type>* bheap) {
	BinomHeap<Key_type>* temp_heap = new BinomHeap<Key_type/*_0*/>;
	temp_heap->mergeHeaps(this, bheap);
	if(temp_heap->head_ == nullptr) {
		return;
	}
	Node<Key_type>* previous_tree = nullptr;
	Node<Key_type>* current_tree = temp_heap->head_;
	Node<Key_type>* next_tree = current_tree->sibling_;
	while(next_tree != nullptr) {
		if((current_tree->degree_ != next_tree->degree_) ||
			(next_tree->sibling_ != nullptr && next_tree->sibling_->degree_ == current_tree->degree_)) {
				previous_tree = current_tree;
				current_tree = next_tree;
		} else {
			if(current_tree->key_ <= next_tree->key_) {
				current_tree->sibling_ = next_tree->sibling_;
				linkTrees(next_tree, current_tree);
			} else {
				if(previous_tree == nullptr)
					temp_heap->head_ = next_tree;
				else
					previous_tree->sibling_ = next_tree;
				linkTrees(current_tree, next_tree);
				current_tree = next_tree;
			}
		}
		next_tree = current_tree->sibling_;
	}
	this->head_ = temp_heap->head_;
	temp_heap = nullptr;
	bheap = nullptr;
}

template<typename Key_type>
Node<Key_type>* BinomHeap<Key_type>::push(const Key_type& in) {
	BinomHeap<Key_type>* temp_heap = new BinomHeap<Key_type>;
	temp_heap->head_ = new Node<Key_type>;
	Node<Key_type>* temp_ptr = temp_heap->head_;
	*(temp_heap->head_) = Node<Key_type>(in);
	unionHeaps(temp_heap);
	++size_;
	return temp_ptr;
}

template<typename Key_type>
void BinomHeap<Key_type>::mergeHeaps(BinomHeap<Key_type>* bheap_1,BinomHeap<Key_type>* bheap_2) {
	Node<Key_type>* ptr_1 = bheap_1->head_;
	Node<Key_type>* ptr_2 = bheap_2->head_;
	Node<Key_type>* cur_temp = nullptr;
	bool flag_first = 1;
	while(1) {
		if(ptr_1 != nullptr) {
			if(ptr_2 != nullptr) {
				if(ptr_1->degree_ <= ptr_2->degree_) {
					if(flag_first) {
						head_ = ptr_1;
						cur_temp = head_;
						flag_first = 0;
					} else {
						cur_temp->sibling_ = ptr_1;
						cur_temp = ptr_1;
					}
					ptr_1 = ptr_1->sibling_;
				} else {
					if(flag_first) {
						head_ = ptr_2;
						cur_temp = head_;
						flag_first = 0;
					} else {
						cur_temp->sibling_ = ptr_2;
						cur_temp = ptr_2;
					}
					ptr_2 = ptr_2->sibling_;
				}
			} else {
				if(flag_first) {
					head_ = ptr_1;
					cur_temp = head_;
					flag_first = 0;
				} else {
					cur_temp->sibling_ = ptr_1;
					cur_temp = ptr_1;
				}
				ptr_1 = ptr_1->sibling_;
			}
		} else {
			if(ptr_2 == nullptr)
				break;
			if(flag_first) {
				head_ = ptr_2;
				cur_temp = head_;
				flag_first = 0;
			} else {
				cur_temp->sibling_ = ptr_2;
				cur_temp = ptr_2;
			}
			ptr_2 = ptr_2->sibling_;
		}
	}
	bheap_2 = bheap_1 = nullptr;
}

template<typename Key_type>
void BinomHeap<Key_type>::pop() {
	Node<Key_type>* current_node = head_;
	Node<Key_type>* ptr_min = current_node;
	Node<Key_type>* prev_ptr_min = nullptr;
	Key_type min = current_node->key_;
	while(current_node != nullptr) {
		if(current_node->key_ < min) {
			prev_ptr_min = ptr_min;
			min = current_node->key_;
			ptr_min = current_node;
		}
		current_node = current_node->sibling_;
	}

	BinomHeap<Key_type>* temp_heap = new BinomHeap<Key_type>;
	if(prev_ptr_min == nullptr)
		head_ = ptr_min->sibling_;
	else
		prev_ptr_min->sibling_ = ptr_min->sibling_;
	temp_heap->head_ = ptr_min;
	ptr_min->sibling_ = nullptr;
	unionHeaps(temp_heap->rotateChildren());
	--size_;
}

template<typename Key_type>
BinomHeap<Key_type>* BinomHeap<Key_type>::rotateChildren() {
	if(head_->degree_ == 0) {
		delete head_;
		head_ = nullptr;
		return this;
	}
	Node<Key_type>* previous_child = nullptr;
	Node<Key_type>* current_child = head_->child_;
	Node<Key_type>* next_child = head_->child_->sibling_;
	while(next_child != nullptr) {
		current_child->sibling_ = previous_child;
		current_child->parent_ = nullptr;
		previous_child = current_child;
		current_child = next_child;
		next_child = current_child->sibling_;
	}
	current_child->parent_ = nullptr;
	current_child->sibling_ = previous_child;
	delete head_;
	head_ = current_child;
	return this;
}

template<typename Key_type>
void BinomHeap<Key_type>::decreaseKey(Node<Key_type>* node, const Key_type& new_key) {
	if(new_key > node->key_)
		return;
	node->key_ = new_key;
	Node<Key_type>* temp_node = node;
	Node<Key_type>* temp_node_parent = node->parent_;
	while(temp_node_parent != nullptr && temp_node->key_ < temp_node_parent->key_) {
		Node<Key_type>* top_node = temp_node_parent->parent_;
		Node<Key_type>* parent_sibling = temp_node_parent->sibling_;
		top_node->child_ = temp_node;
		temp_node_parent->parent_ = temp_node;
		temp_node_parent->sibling_ = temp_node->sibling_;
		temp_node_parent->child_ = temp_node->child_;
		temp_node->parent_ = top_node;
		temp_node->child_ = temp_node_parent;
		temp_node->sibling_ = parent_sibling;

		temp_node = temp_node_parent;
		temp_node_parent = temp_node->parent_;
	}
}

template<typename Key_type>
void BinomHeap<Key_type>::deleteKey(Node<Key_type>* node) {
	decreaseKey(node, Key_type(std::numeric_limits<int>:min));
	pop();
}
#endif