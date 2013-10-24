#include"SNM.h"

int main(){
	SNM::SetsSystem<int> S;
	SNM::Node<int>* q1 = S.addSet(100, 1);
	SNM::Node<int>* q2 = S.addSet(1000, 2);
	SNM::Node<int>* q3 = S.addSet(10, 13);
	SNM::Node<int>* q4 = S.addSet(30, 14);
	SNM::Node<int>* q5 = S.addSet(20, 35);
	SNM::Node<int>* q6 = S.addSet(990, 36);
	SNM::Node<int>* q7 = S.addSet(-1, 77);
	S.connectAtoB(2,1);
	S.connectAtoB(14,1);
	S.connectAtoB(35,1);
	S.connectAtoB(77,36);
	S.connectAtoB(36,1);
	cout << S.find(q6);
	cout << S.find(q6);
	cout << S.find(q2);
	return 0;
}