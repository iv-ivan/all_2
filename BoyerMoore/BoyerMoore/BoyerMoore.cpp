#include "BoyerMoore.h"
#include "PrefixFunc.h"

vector<int> BoyerMoore(const string& str, istream& in) {
	//----------stopTable--
	int stopTable[256];
	for(int i = 0; i < 256; ++i)
		stopTable[i] = 0;

	for(int i = 0; i < str.length(); ++i)
		stopTable[unsigned char(str[i])] = i;
	//-------------------
	vector<int> suffTable(str.length() + 1);
	PrefixFunc pref(str);

	string strReverse(str.length(), 'a');
	for(int i = 0; i < str.length(); ++i)
		strReverse[i] = str[str.length() - i - 1];
	PrefixFunc prefReverse(strReverse);

	for(int i = 0; i < str.length() + 1; ++i)
		suffTable[i] = str.length() - pref[str.length() - 1];

	for(int i = 1; i < str.length(); ++i) {
		int j = prefReverse[i];
		if(j != 0)
			suffTable[j] = min(suffTable[j],  i - j + 1);
	}
	//-----------
	int posEnd = str.length() - 1;
	int posCompare = 0;
	string text = "";
	char c;
	while(in >> c)
		text = text + c;
	//------------
	vector<int> result;
	while(posEnd < text.length()) {
		bool flag = true;
		while(posCompare < str.length()) {
			if(str[str.length() - 1 - posCompare] != text[posEnd - posCompare]) {
				flag = false;
				break;
			}
			++posCompare;
		}

		if(flag) {
			result.push_back(posEnd - str.length() + 1);
			++posEnd;
			posCompare = 0;
		} else {
			if(posCompare > 0)
				posEnd += shift(text[posEnd - posCompare], str[0], str.length() - posCompare - 1, 
				                stopTable[unsigned char(text[posEnd - posCompare])], suffTable[posCompare - 1]);
			else
				posEnd += shift(text[posEnd - posCompare], str[0], str.length() - posCompare - 1, 
				                stopTable[unsigned char(text[posEnd - posCompare])], 1);
			posCompare = 0;
		}
	}
	return result;
}

int shift(unsigned char cInText, unsigned char str0, int indexOfUnequal, int indexOfLastC, int shiftSuff) {
	if(indexOfLastC == 0) {
		if(cInText != str0)
			return indexOfUnequal + 1;
		else
			return indexOfUnequal;
	} else {
		if(indexOfLastC < indexOfUnequal)
			return indexOfUnequal - indexOfLastC;
		else 
			return shiftSuff;
	}
}	