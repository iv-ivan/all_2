#ifndef _SEG_TREE
#define _SEG_TREE
#include<vector>
#include<algorithm>
template<typename T>
class SegmentTree {
public:
	SegmentTree(std::vector<T>& a);
	std::pair<T, int> check(int l, int r);
	void update(int pos, const T& new_val);
	~SegmentTree(){};
private:
	int size_;
	std::vector<std::pair<T, int> > tree_;
	void build_(std::vector<T>& a, int v, int tl, int tr);
	std::pair<T, int> check_(int v, int tl, int tr, int l, int r);
	void update_(int v, int tl, int tr, int pos, const T& new_val);
};
#include"SegmentTree.hpp"
#endif