#include"SNM.h"

int main(){
	SetsSystem<int> S;
	Node<int>* q1 = S.addSet(100, 1);
	Node<int>* q2 = S.addSet(1000, 2);
	Node<int>* q3 = S.addSet(10, 13);
	Node<int>* q4 = S.addSet(30, 14);
	Node<int>* q5 = S.addSet(20, 35);
	Node<int>* q6 = S.addSet(990, 36);
	Node<int>* q7 = S.addSet(-1, 77);
	S.connectAtoB(2,1);
	S.connectAtoB(14,1);
	S.connectAtoB(35,1);
	S.connectAtoB(77,36);
	S.connectAtoB(36,1);
	cout << S.find(q6);
	cout << S.find(q6);
	return 0;
}