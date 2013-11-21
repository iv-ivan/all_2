#include"Fenvik.h"
#include<iostream>

int main() {
	std::vector<int> a;
	for(int i = 0; i < 20; ++i) {
		a.push_back(rand() % 20);
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
	FenvikTree<int> tr(a);
	std::cout << tr.sum(0,19) << std::endl;
	std::cout << tr.sum(5,7) << std::endl;
	std::cout << tr.sum(14,14) << std::endl;
	std::cout << tr.sum(12,15) << std::endl;
	std::cout << tr.sum(8,4) << std::endl;
	return 0;
}