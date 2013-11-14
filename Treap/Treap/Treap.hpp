template<typename type_key, typename type_prior>
Node<type_key, type_prior>* Node<type_key, type_prior>::getParent() {
	return parent_;
}

template<typename type_key, typename type_prior>
Node<type_key, type_prior>* Node<type_key, type_prior>::getL() {
	return l_child_;
}

template<typename type_key, typename type_prior>
Node<type_key, type_prior>* Node<type_key, type_prior>::getR() {
	return r_child_;
}

template<typename type_key, typename type_prior>
void Node<type_key, type_prior>::setParent(Node* new_parent) {
	parent_ = new_parent;
}

template<typename type_key, typename type_prior>
void Node<type_key, type_prior>::setL(Node* new_l_child) {
	l_child_ = new_l_child;
}

template<typename type_key, typename type_prior>
void Node<type_key, type_prior>::setR(Node* new_r_child) {
	r_child_ = new_r_child;
}

template<typename type_key, typename type_prior>
const type_key& Node<type_key, type_prior>::getKey() {
	return key_prior_.first;
}

template<typename type_key, typename type_prior>
const type_prior& Node<type_key, type_prior>::getPrior() {
	return key_prior_.second;
}

template<typename type_key, typename type_prior>
Node<type_key, type_prior>::Node(const type_key& key, const type_prior& prior):parent_(nullptr), l_child_(nullptr), r_child_(nullptr), key_prior_(std::make_pair(key, prior)) {
}

template<typename type_key, typename type_prior>
Node<type_key, type_prior>::~Node() {
}

template<typename type_key, typename type_prior>
Node<type_key, type_prior>::Node(const Node& x):parent_(x.parent_), l_child_(x.l_child_), r_child(x.r_child_), key_prior_(x.key_prior_) {
}

template<typename type_key, typename type_prior>
void Treap<type_key, type_prior>::insert(const type_key& key, const type_prior& prior) {
	Node<type_key, type_prior>* new_node = new Node<type_key, type_prior>(key, prior);
	if(root_ == nullptr) {
		root_ = new_node;
		return;
	}
	std::pair<Node<type_key, type_prior>*, char> place = searchPlace(root_, key, prior, '0');
	switch(place.second) {
	case '0': new_node->setParent(nullptr);root_ = new_node; break;
	case 'r': new_node->setParent(place.first->getParent()); place.first->getParent()->setR(new_node); break;
	case 'l': new_node->setParent(place.first->getParent()); place.first->getParent()->setL(new_node); break;
	case '1': new_node->setParent(place.first); place.first->setL(new_node); return;
	case '2': new_node->setParent(place.first); place.first->setR(new_node); return;
	}
	std::pair<Node<type_key, type_prior>*, Node<type_key, type_prior>*> split_res = Split(place.first, key);
	new_node->setL(split_res.first);
	if(split_res.first != nullptr)
		split_res.first->setParent(new_node);
	new_node->setR(split_res.second);
	if(split_res.second != nullptr)
		split_res.second->setParent(new_node);
}

template<typename type_key, typename type_prior>
std::pair<Node<type_key, type_prior>*, char> Treap<type_key, type_prior>::searchPlace(Node<type_key, type_prior>* cur_node, const type_key& key, const type_prior& prior, char way) {
	if(cur_node == root_ && cur_node->getPrior() > prior)
		return std::make_pair(cur_node, '0');
	if(cur_node->getPrior() > prior)
		return std::make_pair(cur_node, way);
	if(key >= cur_node->getKey())
		if(cur_node->getR() == nullptr)
			return std::make_pair(cur_node, '2');
		else
			return searchPlace(cur_node->getR(), key, prior, 'r');
	if(key < cur_node->getKey())
		if(cur_node->getL() == nullptr)
			return std::make_pair(cur_node, '1');
		else
			return searchPlace(cur_node->getL(), key, prior,  'l');
}

template<typename type_key, typename type_prior>
const type_prior& Treap<type_key, type_prior>::search(const type_key& x) const {
	return deepSearch(root_,x)->getPrior();
}

template<typename type_key, typename type_prior>
Node<type_key, type_prior>* Treap<type_key, type_prior>::deepSearch(Node<type_key, type_prior>* cur_node, const type_key& x) const {
	if(cur_node->getKey() == x)
		return cur_node;
	if(cur_node->getKey() > x)
		return deepSearch(cur_node->getL(),x);
	else
		return deepSearch(cur_node->getR(),x);
}

template<typename type_key, typename type_prior>
void Treap<type_key, type_prior>::erase(const type_key& x) {
	Node<type_key, type_prior>* cur_node = deepSearch(root_, x);
	Node<type_key, type_prior>* cur_node_parent = cur_node->getParent();
	char c;
	if(cur_node_parent == nullptr)
		c = '0';
	else
		if(cur_node == cur_node_parent->getR())
			c = 'r';
		else
			c = 'l';
	Node<type_key, type_prior>* merge_res = Merge(cur_node->getL(), cur_node->getR());
	delete cur_node;
	if(merge_res != nullptr)
		merge_res->setParent(cur_node_parent);
	if(c == 'r')
		cur_node_parent->setR(merge_res);
	else
		if(c == 'l')
			cur_node_parent->setL(merge_res);
		else
			root_ = merge_res;
}

template<typename type_key, typename type_prior>
void Treap<type_key, type_prior>::unionWith(Treap& b) {
	root_ = unionTreaps(this->root_, b.root_);
	b.root_ = nullptr;
}

template<typename type_key, typename type_prior>
Node<type_key, type_prior>* unionTreaps(Node<type_key, type_prior>* a,Node<type_key, type_prior>* b) {
	if(a == nullptr)
		return b;
	if(b == nullptr)
		return a;
	if(a->getPrior() > b->getPrior())
		return unionTreaps(b,a);
	std::pair<Node<type_key, type_prior>*,Node<type_key, type_prior>*> LR = Split(b,a->getKey());
	a->setL(unionTreaps(a->getL(), LR.first));
	if(a->getL() != nullptr)
		a->getL()->setParent(a);
	a->setR(unionTreaps(a->getR(), LR.second));
	if(a->getR() != nullptr)
		a->getR()->setParent(a);
	return a;
}

template<typename type_key, typename type_prior>
Treap<type_key, type_prior>::Treap():root_() {
}

template<typename type_key, typename type_prior>
void Treap<type_key, type_prior>::orderBuild(const std::vector<std::pair<type_key, type_prior> >& a, const int& ind_start, const int& ind_end) {
	Node<type_key,type_prior>* cur_node = root_;
	Node<type_key,type_prior>** cur_node_ptr = new Node<type_key,type_prior>*;
	*cur_node_ptr = cur_node;
	for(int i = ind_start; i <= ind_end; ++i)
		orderInsert(cur_node_ptr,a[i].first,a[i].second);
	delete cur_node_ptr;
	return;
}
//!!!!!!!!!!!!
template<typename type_key, typename type_prior>
void Treap<type_key, type_prior>::orderInsert(Node<type_key,type_prior>** cur_node_ptr, const type_key& key, const type_prior& prior) {
	if(*cur_node_ptr == nullptr) {
		Node<type_key,type_prior>* new_node = new Node<type_key,type_prior>(key, prior);
		if(root_ != nullptr)
			root_->setParent(new_node);
		new_node->setL(root_);
		root_ = new_node;
		*cur_node_ptr = new_node;
		return;
	}
	if((*cur_node_ptr)->getPrior() < prior) {
		Node<type_key,type_prior>* new_node = new Node<type_key,type_prior>(key, prior);
		if((*cur_node_ptr)->getR() != nullptr) {
			new_node->setL((*cur_node_ptr)->getR());
			(*cur_node_ptr)->getR()->setParent(new_node);
		}
		(*cur_node_ptr)->setR(new_node);
		new_node->setParent(*cur_node_ptr);
		*cur_node_ptr = new_node;
		return;
	} else {
		*cur_node_ptr = (*cur_node_ptr)->getParent();
		orderInsert(cur_node_ptr, key, prior);
	}
}

template<typename type_key, typename type_prior>
Treap<type_key, type_prior>::~Treap() {
	deleteNode(root_);
}

template<typename type_key, typename type_prior>
void Treap<type_key, type_prior>::deleteNode(Node<type_key, type_prior>* cur_node) {
	if(cur_node != nullptr) {
		deleteNode(cur_node->getR());
		deleteNode(cur_node->getL());
		delete cur_node;
	}
}

template<typename type_key, typename type_prior>
std::pair<Node<type_key, type_prior>*, Node<type_key, type_prior>*> Split(Node<type_key, type_prior>* cur_node, const type_key& divisor) {
	Node<type_key, type_prior>* L;
	Node<type_key, type_prior>* R;
	if(cur_node->getKey() < divisor) {
		if(cur_node->getR() != nullptr) {
			std::pair<Node<type_key, type_prior>*, Node<type_key, type_prior>*> temp_pair_treaps = Split(cur_node->getR(), divisor);
			if(temp_pair_treaps.first != nullptr) {
				temp_pair_treaps.first->setParent(cur_node);
				cur_node->setR(temp_pair_treaps.first);
				L = cur_node;
				L->setParent(nullptr);
				temp_pair_treaps.first = nullptr;
			} else {
				cur_node->setR(nullptr);
				L = cur_node;
			}

			if(temp_pair_treaps.second != nullptr) {
				R = temp_pair_treaps.second;
				R->setParent(nullptr);
				temp_pair_treaps.second = nullptr;
			} else
				R = nullptr;
		} else {
			L = cur_node;
			L->setParent(nullptr);
			R = nullptr;
		}
	} else {
		if(cur_node->getL() != nullptr) {
			std::pair<Node<type_key, type_prior>*, Node<type_key, type_prior>*> temp_pair_treaps = Split(cur_node->getL(), divisor);
			if(temp_pair_treaps.second != nullptr) {
				temp_pair_treaps.second->setParent(cur_node);
				cur_node->setL(temp_pair_treaps.second);
				R = cur_node;
				R->setParent(nullptr);
				temp_pair_treaps.second = nullptr;
			} else {
				cur_node->setL(nullptr);
				R = cur_node;
			}

			if(temp_pair_treaps.first != nullptr) {
				L = temp_pair_treaps.first;
				L->setParent(nullptr);
				temp_pair_treaps.first = nullptr;
			} else
				L = nullptr;
		} else {
			R = cur_node;
			R->setParent(nullptr);
			L = nullptr;
		}
	}
	return std::make_pair(L, R);
}

template<typename type_key, typename type_prior>
Node<type_key, type_prior>* Merge(Node<type_key, type_prior>* l_node, Node<type_key, type_prior>* r_node) {
	if(l_node == nullptr)
		return r_node;
	if(r_node == nullptr)
		return l_node;
	if(l_node->getPrior() < r_node->getPrior()) {
		l_node->setR(Merge(l_node->getR(), r_node));
		l_node->getR()->setParent(l_node);
		return l_node;
	} else {
		r_node->setL(Merge(l_node, r_node->getL()));
		r_node->getL()->setParent(r_node);
		return r_node;
	}
}

template<typename type_key, typename type_prior>
std::ostream& operator << (std::ostream& out, Treap<type_key, type_prior>& tr) {
	std::vector<std::vector<int>> a(15);
	for(int i = 0; i < 15; ++i)
		a[i].resize(15);
	for(int i = 0; i < 15; ++i)
		for(int j = 0; j < 15; ++j)
			a[i][j] = -100;
	addNode(a, tr.root_);
	for(int i = 0; i < 100; ++i) {
		for(int j = 0; j < 100; ++j)
			if(a[i][j] != -100)
				out << a[i][j];
			else
				out << '-';
		out << std::endl;
	}
	return out;
}

template<typename type_key, typename type_prior>
void addNode(std::vector<std::vector<int> >& a, Node<type_key, type_prior>* tr) {
	if(tr == nullptr)
		return;
	else
		a[tr->getPrior()][tr->getKey()] = tr->getKey();
	if(tr->getL() != nullptr) 
		std::cout << tr->getKey() << " " << tr->getL()->getKey() << std::endl;
	addNode(a, tr->getL());
	if(tr->getR() != nullptr) 
		std::cout << tr->getKey() << " " << tr->getR()->getKey() << std::endl;
	addNode(a, tr->getR());
}