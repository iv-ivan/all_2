#include "Bitap.h"

void checkLast(unsigned int value, int l, vector<pair<int, int> >& positions, int counter, int distance) {
	--l;
	value >>= l;
	if((value & 1) == false)
		positions.push_back(make_pair(counter - l, distance));
}

vector<pair<int, int> > Bitap(const string& str, istream& in) {
	unsigned int mask[256];
	unsigned char c;

	//----------count masks--------
	for(c = 0; c < 255; ++c) {
		unsigned int mask_c = 0;

		for(int i = str.length() - 1; i >= 0; --i) {
			mask_c <<= 1;
			if(str[i] == c)
				++mask_c;
		}
		mask[c] = ~mask_c;
	}

	unsigned int mask_c = 0;

	for(int i = str.length() - 1; i >= 0; --i) {
		if(str[i] == 255)
			++mask_c;
		mask_c <<= 1;
	}
	mask[mask_c] = ~mask_c;
	//------------------------

	int maxDistance;
	in >> maxDistance;

	++maxDistance;

	vector<unsigned int> resultPrev(maxDistance);
	vector<unsigned int> result(maxDistance);

	vector<pair<int, int> > positionsDistance;

	int counter = 0;

	for(int i = 0; i < maxDistance; ++i)
		resultPrev[i] = ~0;

	//----------mainloop--------
	while(in >> c) {
		result[0] = (resultPrev[0] << 1) | mask[c];

		for(int k = 1; k < maxDistance; ++k) {
			unsigned int shiftAndMask = (resultPrev[k] << 1) | mask[c];

			unsigned int insert = shiftAndMask & resultPrev[k-1];
			unsigned int del = shiftAndMask & (result[k-1] << 1);
			unsigned int subst = shiftAndMask & (resultPrev[k-1] << 1);

			result[k] = insert & del & subst;
		}

		for(int k = 0; k < maxDistance; ++k)
			checkLast(result[k], str.length(), positionsDistance, counter, k);
		
		for(int k = 0; k < maxDistance; ++k)
			resultPrev[k] = std::move(result[k]);

		++counter;
	}

	return positionsDistance;
}