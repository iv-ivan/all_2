#ifndef _FENVIK
#define _FENVIK
#include<vector>
template<typename T>
class FenvikTree {
public:
	FenvikTree(const std::vector<T>& a);
	~FenvikTree(){};
	T sum(int l, int r);
private:
	T sum(int r);
	void incr(int i, const T& delta);
	std::vector<T> part_sum_;
};
#include"Fenvik.hpp"
#endif