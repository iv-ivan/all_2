template<typename Key_type>
const Key_type& BinomHeap<Key_type>::top() {
	Node<Key_type>* current_node = head_;
	Node<Key_type>* ptr_min = nullptr;
	int min = std::numeric_limits<int>::max();
	while(current_node != nullptr) {
		if(current_node->key_ < min) {
			min = current_node->key_;
			ptr_min = current_node;
		}
		current_node = current_node->sibling_;
	}
	return ptr_min->key_;
}

template<typename Key_type_0>
void linkTrees(Node<Key_type_0>* btree_1, Node<Key_type_0>* btree_2) {
	btree_1->parent_ = btree_2;
	btree_1->sibling_ = btree_2->child_;
	btree_2->child_ = btree_1;
	++(btree_2->degree_);
}

template<typename Key_type_0>
Node<Key_type_0>* unionHeaps(BinomHeap<Key_type_0>* bheap_1, BinomHeap<Key_type_0>* bheap_2) {
	BinomHeap<Key_type_0>* temp_heap = new BinomHeap<Key_type_0>;
	mergeHeaps(temp_heap, bheap_1, bheap_2);
	if(temp_heap->head_ == nullptr)
		return temp_heap->head_;
	Node<Key_type_0>* previous_tree = nullptr;
	Node<Key_type_0>* current_tree = temp_heap->head_;
	Node<Key_type_0>* next_tree = current_tree->sibling_;
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
	Node<Key_type_0>* ret = temp_heap->head_;
	temp_heap = nullptr;
	bheap_1 = bheap_2 = nullptr;
	return ret;
}

template<typename Key_type>
void BinomHeap<Key_type>::push(const Key_type& in) {
	BinomHeap<Key_type>* temp_heap = new BinomHeap<Key_type>;
	temp_heap->head_ = new Node<Key_type>;
	*(temp_heap->head_) = Node<Key_type>(in);
	this->head_ = unionHeaps<Key_type>(this, temp_heap);
	++size_;
}

template<typename Key_type_0>
void mergeHeaps(BinomHeap<Key_type_0>* temp_heap,BinomHeap<Key_type_0>* bheap_1,BinomHeap<Key_type_0>* bheap_2) {
	Node<Key_type_0>* ptr_1 = bheap_1->head_;
	Node<Key_type_0>* ptr_2 = bheap_2->head_;
	Node<Key_type_0>* cur_temp = nullptr;
	bool flag_first = 1;
	while(1) {
		if(ptr_1 != nullptr) {
			if(ptr_2 != nullptr) {
				if(ptr_1->degree_ <= ptr_2->degree_) {
					if(flag_first) {
						temp_heap->head_ = ptr_1;
						cur_temp = temp_heap->head_;
						flag_first = 0;
					} else {
						cur_temp->sibling_ = ptr_1;
						cur_temp = ptr_1;
					}
					ptr_1 = ptr_1->sibling_;
				} else {
					if(flag_first) {
						temp_heap->head_ = ptr_2;
						cur_temp = temp_heap->head_;
						flag_first = 0;
					} else {
						cur_temp->sibling_ = ptr_2;
						cur_temp = ptr_2;
					}
					ptr_2 = ptr_2->sibling_;
				}
			} else {
				if(flag_first) {
					temp_heap->head_ = ptr_1;
					cur_temp = temp_heap->head_;
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
				temp_heap->head_ = ptr_2;
				cur_temp = temp_heap->head_;
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
	Node<Key_type>* ptr_min = nullptr;
	Node<Key_type>* prev_ptr_min = nullptr;
	int min = std::numeric_limits<int>::max();
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
	head_ = unionHeaps(this, temp_heap->rotate_children());
	--size_;
}

template<typename Key_type>
BinomHeap<Key_type>* BinomHeap<Key_type>::rotate_children() {
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