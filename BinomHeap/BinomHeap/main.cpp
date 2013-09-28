#include<iostream>
#include"BinomHeap.h"

using namespace std;

int main() {
	BinomHeap<int> a;
	a.push(10);
	a.push(100);//
	a.push(1000);//
	a.push(100);//
	a.push(1);
	a.push(7);
	a.push(88);//
	a.push(9999);//
	a.pop();
	a.pop();
	a.push(0);
	a.push(101);//
	a.push(99);//
	a.push(3);
	a.push(33);
	a.push(907);//
	a.push(8);
	cout<<a.top();
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
	a.pop();
	a.pop();
	a.pop();
	return 0;
}