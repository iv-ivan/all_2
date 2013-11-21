template<typename T>
SegmentTree<T>::SegmentTree(std::vector<T>& a) {
	tree_.resize(4*a.size());
	size_ = a.size();
	build_(a, 1, 0, size_ - 1);
}

template<typename T>
void SegmentTree<T>::build_(std::vector<T>& a, int v, int tl, int tr) {
	if(tl == tr)
		tree_[v] = std::make_pair(a[tl], tl);
	else {
		int tm = (tl + tr);
		tm >>= 1;
		int temp_v = v;
		v <<=1;
		build_(a, v, tl, tm);
		build_(a, v+1, tm+1, tr);
		if(tree_[v].first < tree_[v + 1].first)
			tree_[temp_v] = tree_[v];
		else
			tree_[temp_v] = tree_[v + 1];
	}
}

template<typename T>
std::pair<T, int> SegmentTree<T>::check(int l, int r) {
	if(l <= r)
		return check_(1, 0, size_ - 1, l, r);
	else
		return check_(1, 0, size_ - 1, r, l);
}

template<typename T>
std::pair<T, int> SegmentTree<T>::check_(int v, int tl, int tr, int l, int r) {
	if(l > r)
		return std::make_pair(0, -1);
	if(l == tl && r == tr)
		return tree_[v];
	int tm = tl + tr;
	tm >>= 1;
	v <<= 1;
	std::pair<T, int> val1 = check_(v, tl, tm, l, std::min(r, tm));
	std::pair<T, int> val2 = check_(v + 1, tm + 1, tr, std::max(l, tm + 1), r);
	if(val1.second == -1)
		return val2;
	if(val2.second == -1)
		return val1;
	if(val1.first < val2.first)
		return val1;
	else
		return val2;
}

template<typename T>
void SegmentTree<T>::update(int pos, const T& new_val) {
	update_(1, 0, size_ - 1, pos, new_val);
}

template<typename T>
void SegmentTree<T>::update_(int v, int tl, int tr, int pos, const T& new_val) {
	if(tl == tr)
		tree_[v].first = new_val;
	else {
		int tm = tl + tr;
		tm >>= 1;
		int temp_v = v;
		v <<= 1;
		if(pos <= tm)
			update_(v, tl, tm, pos, new_val);
		else
			update_(v + 1, tm + 1, tr, pos, new_val);
		if(tree_[v].first < tree_[v + 1].first)
			tree_[temp_v] = tree_[v];
		else
			tree_[temp_v] = tree_[v + 1];
	}
}