#ifndef _PREFIX_H
#define _PREFIX_H
#include <vector>

using namespace std;

class PrefixFunc {
public:
	PrefixFunc(const string& str);
	~PrefixFunc();
	int operator [] (int i);
private:
	string str_;
	vector<int> values_;
	int previousValue_;
	void buildPrefixFunc();
};
#endif