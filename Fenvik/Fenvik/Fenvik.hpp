template<typename T>
FenvikTree<T>::FenvikTree(const std::vector<T>& a) {
	part_sum_.resize(a.size());
	for(int i = 0; i < (int)a.size(); ++i)
		incr(i, a[i]);
}

template<typename T>
T FenvikTree<T>::sum(int l, int r) {
	if(l <= r)
		return sum(r) - sum(l - 1);
	else
		return sum(l) - sum(r - 1);
}

template<typename T>
void FenvikTree<T>::incr(int i, const T& delta) {
	for(;i < part_sum_.size(); i = (i | (i + 1)))
		part_sum_[i] += delta;
}

template<typename T>
T FenvikTree<T>::sum(int r) {
	T result = 0;
	for(;r >= 0; r = (r & (r + 1)) - 1)
		result += part_sum_[r];
	return result;
}

