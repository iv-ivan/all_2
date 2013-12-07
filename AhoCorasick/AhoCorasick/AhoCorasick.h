#ifndef _AHO_CORASICK_
#define _AHO_CORASICK_

#include <vector>
#include <string>
#include <iostream>
#include <list>

using namespace std;

struct vertex {
	int next[256];
	vector<int> childs;
	int end;//-1 if not end and n>=1 if end of needles[n]
	int parent;
	unsigned char parentChar;
	int link;
	int prevEnd;//index, following links
	//int go[K];
};

vector<pair<int, int> > AhoCorasick(const vector<string>& needles, istream& in);
void addString(vector<vertex>& vArray, int& size, const string& str, int No);
void addReferences(vector<vertex>& vArray);
void dfsAdd(vector<vector<int> >& levels, const vector<vertex>& vArray, int v, int h);
void buildReferences(const vector<int>& vertices, vector<vertex>& vArray);
vector<pair<int, int> > find(vector<vertex>& vArray, istream& in);

#endif