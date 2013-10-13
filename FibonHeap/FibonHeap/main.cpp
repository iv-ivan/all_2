#include"FibonHeap.h"
#include<iostream>

int main() {
	FibonHeap<int> a;
	a.push(10);
	a.push(10);
	std::cout << a.top() << std::endl;
	a.pop();
	a.push(0);
	a.push(-10);
	a.push(100);
	Node<int>* x = a.push(1000);
	a.push(1);
	a.push(0);
	Node<int>* y = a.push(-1);
	std::cout << a.top() << std::endl;
	a.push(-2);
	a.push(-100);
	std::cout << a.top() << std::endl;
	a.pop();
	a.pop();
	a.decreaseKey(y,-5);
	a.decreaseKey(x,-5);// מעהוכüםûי
	a.push(100);
	a.push(1000);
	y = a.push(31);
	a.push(30);
	x = a.push(3100);
	a.push(31000);
	a.push(31);
	a.decreaseKey(y,-50);
	a.decreaseKey(x, 0);
	a.push(30);
	a.pop();
	a.pop();
	a.pop();
	a.pop();
	a.pop();
	a.pop();
	a.pop();
	a.pop();
	a.pop();
	a.pop();
	return 0;
}