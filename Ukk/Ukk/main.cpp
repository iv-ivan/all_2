#include"Ukk.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
	vector<string> z;
	z.push_back("a");
	z.push_back("12z");
	z.push_back("bbc");
	z.push_back("bb");
	z.push_back("t");
	z.push_back("a");
	z.push_back("bab");
	z.push_back("abbbabbc12zzz");
	z.push_back("as");
	z.push_back("tt");
	ifstream in("input.txt");
	vector<list<int> > x = Ukk(z, in);
	return 0;
}