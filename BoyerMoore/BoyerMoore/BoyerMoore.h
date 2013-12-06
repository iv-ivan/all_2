#ifndef _BOYERMOORE_H_
#define _BOYERMOORE_H_

#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> BoyerMoore(const string& a, istream& in);
int shift(unsigned char cInText, unsigned char str0, int indexOfUnequal, int indexOfLastC, int shiftSuff);
#endif