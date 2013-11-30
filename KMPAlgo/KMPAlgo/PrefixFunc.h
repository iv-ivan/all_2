#ifndef _PREFIX_H
#define _PREFIX_H
#include <vector>

using namespace std;

class PrefixFunc {
public:
	int calculate(char c);
	PrefixFunc(const string& str);
	~PrefixFunc();
private:
	string str_;
	vector<int> values_;
	int previousValue_;
	int positionUndefined_;
	void buildPrefixFunc();
};
#endif