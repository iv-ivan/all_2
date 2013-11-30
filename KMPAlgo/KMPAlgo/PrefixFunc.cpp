#include "PrefixFunc.h"
int PrefixFunc::calculate(char c) {
	int j = previousValue_;
	while(j > 0 && c != str_[j] || j == positionUndefined_)
			j = values_[j - 1];
		if(c == str_[j])
			++j;
		previousValue_ = j;
		return j;
}

PrefixFunc::PrefixFunc(const string& str) {
	positionUndefined_ = str.length();
	values_.resize(positionUndefined_);
	str_ = str;
	values_[0] = 0;
	previousValue_ = 0;
	buildPrefixFunc();
}

PrefixFunc::~PrefixFunc() {
}

void PrefixFunc::buildPrefixFunc() {
	for(int i = 1; i < positionUndefined_; ++i) {
		int j = values_[i - 1];
		while(j > 0 && str_[i] != str_[j])
			j = values_[j - 1];
		if(str_[i] == str_[j])
			++j;
		values_[i] = j;
	}
}