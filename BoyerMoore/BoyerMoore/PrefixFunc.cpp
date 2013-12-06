#include "PrefixFunc.h"

PrefixFunc::PrefixFunc(const string& str) {
	values_.resize(str.length());
	str_ = str;
	values_[0] = 0;
	previousValue_ = 0;
	buildPrefixFunc();
}

PrefixFunc::~PrefixFunc() {
}

void PrefixFunc::buildPrefixFunc() {
	for(int i = 1; i < str_.length(); ++i) {
		int j = values_[i - 1];
		while(j > 0 && str_[i] != str_[j])
			j = values_[j - 1];
		if(str_[i] == str_[j])
			++j;
		values_[i] = j;
	}
}

int PrefixFunc::operator [] (int i) {
	return values_[i];
}