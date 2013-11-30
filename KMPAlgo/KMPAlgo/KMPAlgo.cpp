#include <iostream>
#include "PrefixFunc.h"

using namespace std;

vector<int> KMPAlgo(const string& str, istream& in) {
	PrefixFunc func(str);

	int n = str.length();
	int position = -n;

	vector<int> result;
	char c;
	while(in >> c) {
		++position;
		if(func.calculate(c) == n)
			result.push_back(position);
	}
	return result;
}