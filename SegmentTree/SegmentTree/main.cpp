#include"SegmentTree.h"
#include<iostream>
int main() {
	std::vector<int> a;
	for(int i = 0; i < 20; ++i) {
		a.push_back(rand() % 15);
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
	SegmentTree<int> tr(a);
	tr.update(19, 100);
	std::cout << tr.check(4, 7).first << " " << tr.check(4, 7).second << std::endl;
	std::cout << tr.check(14, 3).first << " " << tr.check(14, 3).second << std::endl;
	std::cout << tr.check(18, 19).first << " " << tr.check(18, 19).second << std::endl;
	std::cout << tr.check(0, 19).first << " " << tr.check(0, 19).second << std::endl;
	std::cout << tr.check(12, 17).first << " " << tr.check(12, 17).second << std::endl;
	return 0;
}