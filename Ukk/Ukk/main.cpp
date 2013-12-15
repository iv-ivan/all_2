#include"Ukk.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
	vector<string> z;
	z.push_back("123");
	ifstream in("input.txt");
	Ukk(z, in);
	return 0;
}