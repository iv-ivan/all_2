#include<vector>
#include<cstdlib>
#include"Treap.h"
#include"RMQ.h"
int main() {
	//my_treap::Treap<int,int> a;
	/*my_treap::Treap<int, int> b;
	b.insert(1,1);
	b.insert(2,5);
	b.insert(0,2);
	b.insert(8,4);
	a.insert(1,11);
	b.insert(8,8);
	b.insert(2,2);
	b.insert(3,0);
	b.insert(6,7);
	b.insert(1,5);
	std::cout << a;
	std::cout << std::endl << b << std::endl;
	a.unionWith(b);
	std::cout << a;*/
	std::vector<int> aa;
	for(int i = 0; i < 15;++i) {
		aa.push_back(rand() % 15);
		std::cout << aa[i] << " ";
	}
	RMQ<int> b(aa);
	std::cout << std::endl << b.getMin(0,4).first << " " << b.getMin(0,4).second;
	std::cout << std::endl << b.getMin(8,9).first << " " << b.getMin(8,9).second;
	//std::cout << a;
	return 0;
}