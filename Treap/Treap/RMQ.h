#ifndef RMQ_
#define RMQ_
#include<vector>
#include<cmath>
#include<algorithm>
namespace my_treap {
	template<typename type_key, typename type_prior>
	class Treap;
}
template<typename type_val>
class RMQ {
public:
	std::pair<int,type_val> getMin(int i, int j);
	RMQ(const std::vector<type_val>&);
	~RMQ(){};
private:
	std::vector<int> first_pos_;//position in farah_vector of element with index [i]
	std::vector<std::pair<int, type_val>> farah_vector_;//index in input array, value for minimum
	std::vector<int> depth_;//depth_[i] = depth of node of farah_vector_[i]

	void treapToRMQ(my_treap::Treap<int, type_val>& temp_treap);
	void DFS(my_treap::Node<int, type_val>* node, int* depth, int* step);
	int n_;
	int size_of_last_;
	int size_of_block_;
	int num_of_blocks_;
	std::vector<int> mapping_to_standard_types_of_blocks;
	std::vector<std::vector<std::vector<int> > > precalc_;//type of block - i - j
	std::vector<std::vector<int>> sparse_table_;
	std::vector<int> vector_min_blocks;

	int calcSizeOfLast();
	int calcNumOfBlocks();
	void initMapping_to_standard_types_of_blocks();
	void initPrecalc();
	void initSparse_table();
	int code(int);
	int lastCode();
	void fillPrecalc();
	void decode(int i, std::vector<int>& a);
	int extractMin(int x, int y, std::vector<int>& cur_code);
	void fillSparseTable(int i, int j);
	int getSparseElement(int i, int j);
};
#include"RMQ.hpp"
#endif