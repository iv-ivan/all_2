#include <iostream>
#include "AhoCorasick.h"
#include <string>
#include <vector>

using namespace std;

int main() {
	vector<string> a;
	a.push_back("Nel");
	a.push_back("2");
	a.push_back("afr");
	a.push_back("fr");
	a.push_back("Man");
	a.push_back("is");
	vector<pair<int, int> > c = AhoCorasick(a, cin);
	for(int i = 0; i < c.size(); ++i) {
		cout << c[i].first << " " << a[c[i].second] << endl;
	}
	return 0;
}