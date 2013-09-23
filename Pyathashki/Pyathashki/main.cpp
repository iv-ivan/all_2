#include"CurState.h"
#include<iostream>
int main() {
	CurState A;
	A.solve();
	std::vector<int> out = A.solution();
	for(int i = 0; i < out.size(); ++i){
		std::cout << out[i] << std::endl;
	}
	int z;
	std::cin >> z;
	return 0;
}