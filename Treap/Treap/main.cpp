#include"Treap.h"
int main() {
	my_treap::Treap<int,int> a;
	a.insert(2,4);
	std::cout << a << std::endl;
	a.insert(6,2);
	std::cout << a << std::endl;
	a.insert(0,3);
	std::cout << a << std::endl;
	a.insert(7,10);
	std::cout << a << std::endl;
	a.insert(13,8);
	std::cout << a << std::endl;
	a.insert(5,1);
	std::cout << a << std::endl;
	a.erase(7);//------------------------
	std::cout << a << std::endl;
	a.insert(14,4);
	std::cout << a << std::endl;
	a.insert(3,3);
	std::cout << a << std::endl;
	a.insert(4,6);
	std::cout << a << std::endl;
	a.insert(8,2);
	std::cout << a << std::endl;
	a.insert(9,7);
	std::cout << a << std::endl;
	a.erase(14);//------------------------
	std::cout << a << std::endl;
	a.erase(5);//------------------------
	std::cout << a << std::endl;
	a.erase(2);//------------------------
	std::cout << a << std::endl;
	a.erase(6);//------------------------
	std::cout << a << std::endl;
	a.erase(0);//------------------------
	std::cout << a << std::endl;
	a.erase(3);//------------------------
	std::cout << a << std::endl;
	a.erase(9);//------------------------
	std::cout << a << std::endl;
	a.erase(8);//------------------------
	std::cout << a << std::endl;
	a.erase(4);//------------------------
	std::cout << a << std::endl;
	a.erase(13);//------------------------
	std::cout << a << std::endl;
	return 0;
}