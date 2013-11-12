template <typename type_val>
RMQ<type_val>::RMQ(const std::vector<type_val>& vec){
	std::vector<std::pair<int, type_val>> arr;
	for(int i = 0; i < vec.size(); ++i) {
		arr.push_back(std::make_pair(i,vec[i]));
		first_pos_.push_back(-1);
	}

	my_treap::Treap<int,type_val> temp_treap;
	temp_treap.orderBuild(arr, 0, arr.size() - 1);

	treapToRMQ(temp_treap);
}

template <typename type_val>
void RMQ<type_val>::treapToRMQ(my_treap::Treap<int, type_val>& treap) {
	int* depth = new int;
	int* step = new int;
	*depth = 0;
	*step = 0;
	DFS(treap.root_,depth,step);
	delete depth;
	delete step;
}

template <typename type_val>
void RMQ<type_val>::DFS(my_treap::Node<int, type_val>* node, int* depth, int* step) {
	if(node == nullptr) {
		*step -= 1;
		return;
	}
	int index = node->key_prior_.first;
	depth_.push_back(*depth);
	farah_vector_.push_back(std::make_pair(index, node->key_prior_.second));
	first_pos_[index] = depth_.size()-1;

	*depth += 1;
	*step += 1;
	DFS(node->getL(), depth, step);
	*depth -= 1;
	if(node->getL() != nullptr) {
		depth_.push_back(*depth);
		farah_vector_.push_back(std::make_pair(index, node->key_prior_.second));
	}

	*depth += 1;
	*step += 1;
	DFS(node->getR(), depth, step);
	*depth -= 1;
	if(node->getR() != nullptr) {
		depth_.push_back(*depth);
		farah_vector_.push_back(std::make_pair(index, node->key_prior_.second));
	}
}
