#ifndef RMQ_
#define RMQ_
#include<vector>
namespace my_treap {
	template<typename type_key, typename type_prior>
	class Treap;
}
template<typename type_val>
class RMQ {
public:
	//type_val get_min(std::vector<type_val>& a, int i, int j);
	RMQ(const std::vector<type_val>&);
	~RMQ(){};
private:
	std::vector<int> first_pos_;//position in farah_vector of element with index [i]
	std::vector<std::pair<int, type_val>> farah_vector_;//index in input array, value for minimum
	std::vector<int> depth_;//depth_[i] = depth of node of farah_vector_[i]

	void treapToRMQ(my_treap::Treap<int, type_val>& temp_treap);
	void DFS(my_treap::Node<int, type_val>* node, int* depth, int* step);
};
#include"RMQ.hpp"
#endif