#ifndef _BITAP_
#define _BITAP_

#include <iostream>
#include <vector>

using namespace std;

void checkLast(unsigned int value, int l, vector<pair<int, int> >& positions, int counter, int distance);

vector<pair<int, int> > Bitap(const string& str, istream& in);
#endif