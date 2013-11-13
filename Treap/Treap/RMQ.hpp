template <typename type_val>
RMQ<type_val>::RMQ(const std::vector<type_val>& vec){
	std::vector<std::pair<int, type_val>> arr;
	for(int i = 0; i < (int)vec.size(); ++i) {
		arr.push_back(std::make_pair(i,vec[i]));
		first_pos_.push_back(-1);
	}

	my_treap::Treap<int,type_val> temp_treap;
	temp_treap.orderBuild(arr, 0, arr.size() - 1);
	n_ = arr.size();
	
	treapToRMQ(temp_treap);
	//build blocks
	size_of_block_ = int(ceil(log(depth_.size())/(2*log(2))));
	num_of_blocks_ = calcNumOfBlocks();
	size_of_last_ = calcSizeOfLast();
	initMapping_to_standard_types_of_blocks();//from 0 to 2^(size_of_block + 1) mapping from blocks-in_array to standard blocks
	initPrecalc();//from i(0...size_of_block-1) to j(i...size_of_block-1) min on this segment
	initSparse_table();//build sparse table for blocks
}

template <typename type_val>
void RMQ<type_val>::initSparse_table() {
	vector_min_blocks.resize(num_of_blocks_);
	for(int i = 0; i < num_of_blocks_ - 1; ++i)
		vector_min_blocks[i] =  depth_[precalc_[mapping_to_standard_types_of_blocks[i]][0][size_of_block_-1] + size_of_block_*i];
	vector_min_blocks[num_of_blocks_ - 1] = depth_[precalc_[mapping_to_standard_types_of_blocks[num_of_blocks_ - 1]][0][size_of_last_-1] + size_of_block_*(num_of_blocks_ - 1)];

	//for(int j = n_; j < 2^(int(ceil(log(n_)/log(2)))); ++j)//push to back max_int to make n_ = 2^t
	//	vector_min_blocks.push_back(100000);

	sparse_table_.resize(num_of_blocks_);
	for(int j = 0; j < num_of_blocks_; ++j) {
		sparse_table_[j].resize(1+int(floor(log(num_of_blocks_)/log(2))));
		for(int i = 0; i < (int)sparse_table_[j].size(); ++i)
			sparse_table_[j][i] = -1;
	}

	for(int j = 0; j < (int)sparse_table_[0].size(); ++j)
		for(int i = 0; i < num_of_blocks_; ++i)
			fillSparseTable(i,j);
}

template <typename type_val>
void RMQ<type_val>::fillSparseTable(int i, int j) {
	if(i >= num_of_blocks_ || j >= (int)sparse_table_[i].size())
		return;
	if(sparse_table_[i][j] != -1)
		return;
	if(j==0) {
		sparse_table_[i][j] = i;
		return;
	}
	if(getSparseElement(i,j-1) == -1)
		fillSparseTable(i,j-1);
	int x0 = 1;
	x0 <<= (j-1);
	x0 += i;
	if(getSparseElement(x0,j-1) == -1)
		fillSparseTable(x0,j-1);
	if(x0 >= num_of_blocks_) {
		sparse_table_[i][j] = sparse_table_[i][j-1];
		return;
	}
	if(vector_min_blocks[sparse_table_[i][j-1]] < vector_min_blocks[sparse_table_[x0][j-1]])
		sparse_table_[i][j] = sparse_table_[i][j-1];
	else
		sparse_table_[i][j] = sparse_table_[x0][j-1];
}

template <typename type_val>
int RMQ<type_val>::getSparseElement(int i, int j) {
	if(i >= num_of_blocks_ || j >= (int)sparse_table_[i].size())
		return -1;
	else
		return sparse_table_[i][j];
}

template <typename type_val>
int RMQ<type_val>::calcNumOfBlocks() {
	return (int)(ceil(1.0 * depth_.size() / size_of_block_));
}

template <typename type_val>
int RMQ<type_val>::calcSizeOfLast() {
	return depth_.size() - size_of_block_ * (num_of_blocks_ - 1);
}

template <typename type_val>
void RMQ<type_val>::initMapping_to_standard_types_of_blocks() {
	mapping_to_standard_types_of_blocks.resize(num_of_blocks_);

	for(int i = 0; i < num_of_blocks_ - 1; ++i)
		mapping_to_standard_types_of_blocks[i] = code(i);//code depth_[i*size_of_block]-depth[(i+1)*size_of_block]
	if(size_of_last_ == size_of_block_)
		mapping_to_standard_types_of_blocks[num_of_blocks_ - 1] = code(num_of_blocks_ - 1);
	else
		mapping_to_standard_types_of_blocks[num_of_blocks_ - 1] = lastCode();
}

template <typename type_val>
int RMQ<type_val>::code(int i) {
	int code_int = 0;
	for(int j = i * size_of_block_ + 1; j < (i + 1) * size_of_block_; ++j) {
		code_int <<= 1;
		if(depth_[j] > depth_[j-1])
			++code_int;
	}
	return code_int;
}

template <typename type_val>
int RMQ<type_val>::lastCode() {
	int code_int = 0;
	for(int j = (num_of_blocks_ - 1) * size_of_block_ + 1; j < n_; ++j) {
		code_int <<= 1;
		if(depth_[j] > depth_[j-1])
			++code_int;
	}
	for(int j = size_of_last_; j < size_of_block_; ++j) {
		code_int <<= 1;
		++code_int;
	}
	return code_int;
}

template <typename type_val>
void RMQ<type_val>::initPrecalc() {
	int  number_of_stand_blocks = 1;
	number_of_stand_blocks <<= size_of_block_ - 1;//because block[0] is 0
	precalc_.resize(number_of_stand_blocks);

	for(int i = 0; i < number_of_stand_blocks; ++i) {
		precalc_[i].resize(size_of_block_);
		for(int j = 0; j < size_of_block_; ++j)
			precalc_[i][j].resize(size_of_block_);
	}

	fillPrecalc();
}

template <typename type_val>
void RMQ<type_val>::fillPrecalc() {
	std::vector<int> cur_code(size_of_block_);
	cur_code[0] = 0;
	for(int i = 0; i < (int)precalc_.size(); ++i) {
		decode(i,cur_code);
		//std::cout << cur_code[0] << cur_code[1] << cur_code[2] << cur_code[3] << std::endl;
		for(int x = 0; x < size_of_block_; ++x)
			for(int y = x; y < size_of_block_; ++y)
				precalc_[i][x][y] = extractMin(x, y, cur_code);
	}
}

template <typename type_val>
void RMQ<type_val>::decode(int i, std::vector<int>& a) {
	int i_l = i;
	for(int j = 1; j < size_of_block_; ++j) {
		i_l >>= 1;
		i_l <<= 1;
		a[size_of_block_ - j] = (i - i_l);
		i >>= 1;
		i_l >>= 1;
	}
}

template <typename type_val>
int RMQ<type_val>::extractMin(int x, int y, std::vector<int>& cur_code) {
	int min = 0;
	int cur_value = 0;
	int ind_min = x;
	for(int i = x + 1; i <= y; ++i) {
		if(cur_code[i] == 1)
			++cur_value;
		else
			--cur_value;
		if(cur_value < min) {
			min = cur_value;
			ind_min = i;
		}
	}
	return ind_min;
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

template <typename type_val>
std::pair<int,type_val> RMQ<type_val>::getMin(int i, int j) {
	if(first_pos_[i] > first_pos_[j]) return getMin(j,i);
	int block_i = first_pos_[i] / size_of_block_;
	int block_j = first_pos_[j] / size_of_block_;
	if(block_i == block_j)
		return farah_vector_[precalc_[mapping_to_standard_types_of_blocks[block_i]][first_pos_[i] - block_i*size_of_block_][first_pos_[j] - block_i*size_of_block_]+block_i*size_of_block_];
	else {
		std::pair<int,type_val> min1 = farah_vector_[precalc_[mapping_to_standard_types_of_blocks[block_i]][first_pos_[i] - block_i*size_of_block_][size_of_block_ - 1]+block_i*size_of_block_];
		std::pair<int,type_val> min3 = farah_vector_[precalc_[mapping_to_standard_types_of_blocks[block_j]][0][first_pos_[j] - block_j*size_of_block_]+block_j*size_of_block_];
		if(block_i + 1 < block_j) {
			int power = int(ceil(log(block_j - 1 - block_i)));
			int power_ = 1;
			power_ <<= power;
			std::pair<int,type_val> min2;
			if(vector_min_blocks[sparse_table_[block_i+1][power]] < vector_min_blocks[sparse_table_[block_j-power_][power]]) {
				int no_block = sparse_table_[block_i+1][power];
				min2 = std::make_pair(no_block*size_of_block_ + precalc_[no_block][0][size_of_block_-1], vector_min_blocks[no_block]);
			} else {
				int no_block = sparse_table_[block_j-power_][power];
				min2 = std::make_pair(no_block*size_of_block_ + precalc_[no_block][0][size_of_block_-1], vector_min_blocks[no_block]);
			}
			type_val min_from_3 = std::min(std::min(min1.second,min2.second),min3.second);
			if(min1.second == min_from_3)
				return min1;
			if(min2.second == min_from_3)
				return min2;
			if(min3.second == min_from_3)
				return min3;
		} else {
			type_val min_from_2 = std::min(min1.second,min3.second);
			if(min1.second == min_from_2)
				return min1;
			if(min3.second == min_from_2)
				return min3;
		}
	}
}