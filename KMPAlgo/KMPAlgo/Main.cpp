#include <iostream>
#include "KMPAlgo.h"

using namespace std;

int main() {
	string a = "abab";
	vector<int> res = KMPAlgo(a,cin);
	for(int i = 0; i < res.size(); ++i)
		cout << res[i] << endl;
	return 0;
}