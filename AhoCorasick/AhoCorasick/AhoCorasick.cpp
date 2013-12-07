#include "AhoCorasick.h"

using namespace std;
 
vector<pair<int, int> > AhoCorasick(const vector<string>& needles, istream& in) {
	vector<vertex> vArray;
	int maxSize = 0;
	for(int i = 0; i < needles.size(); ++i)
		maxSize += needles[i].size();
	vArray.resize(maxSize + 1);
	//-----init---
	for(int i = 0; i < 256; ++i)
		vArray[0].next[i] = -1;

	vArray[0].parent = vArray[0].end = vArray[0].prevEnd = -1;
	vArray[0].link = 0;
	int size = 1;
	//----------
	for(int i = 0; i < needles.size(); ++i)
		addString(vArray, size, needles[i], i);

	addReferences(vArray);

	//vector<int> a;
	//return a;
	return find(vArray, in);
}

void addString(vector<vertex>& vArray, int& size, const string& str, int No) {
	int v = 0;
	for(int i = 0; i < str.length(); ++i) {
		unsigned char c = str[i];
		if(vArray[v].next[c] == -1) {
			for(int j = 0; j < 256; ++j)
				vArray[size].next[j] = -1;
			vArray[size].parent = v;
			vArray[size].link = 0;
			vArray[size].end = -1;
			vArray[size].prevEnd = -1;
			vArray[size].parentChar = c;
			vArray[v].childs.push_back(size);
			vArray[v].next[c] = size++;
		}
		v = vArray[v].next[c];
	}
	vArray[v].end = No;
}

void addReferences(vector<vertex>& vArray) {
	vector<vector<int> > levels;
	levels.resize(1);
	levels[0].push_back(0);
	for(int i = 0; i < vArray[0].childs.size(); ++i)
		dfsAdd(levels, vArray, vArray[0].childs[i], 1);
	for(int i = 2; i < levels.size(); ++i)
		buildReferences(levels[i], vArray);
}

void dfsAdd(vector<vector<int> >& levels, const vector<vertex>& vArray, int v, int h) {
	if(levels.size() <= h)
		levels.resize(levels.size() + 1);
	levels[h].push_back(v);
	for(int i = 0; i < vArray[v].childs.size(); ++i)
		dfsAdd(levels, vArray, vArray[v].childs[i], h + 1);
}

void buildReferences(const vector<int>& vertices, vector<vertex>& vArray) {
	for(int i = 0; i < vertices.size(); ++i) {
		int curV = vertices[i];
		int curParent;
		unsigned char curC;
		int parentRef;
		curParent = vArray[curV].parent;
		curC = vArray[curV].parentChar;
		parentRef = vArray[curParent].link;
		while(1) {
			if(parentRef ==0)
				break;
			if(vArray[parentRef].next[curC] != -1)
				break;
			parentRef = vArray[parentRef].link;
		}
		if(vArray[parentRef].next[curC] != -1) {
			vArray[vertices[i]].link = vArray[parentRef].next[curC];
			if(vArray[vArray[parentRef].next[curC]].end != -1)
				vArray[vertices[i]].prevEnd = vArray[parentRef].next[curC];
			else
				vArray[vertices[i]].prevEnd = vArray[vArray[parentRef].next[curC]].prevEnd;
		}
	}
}

vector<pair<int, int> > find(vector<vertex>& vArray, istream& in) {
	unsigned char c;
	int v = 0;
	int position = -1;
	vector<pair<int, int> > result;
	while(in >> noskipws >> c) {
		++position;
		int vCopy = v;
		while(1) {
			if(vArray[v].next[c] != -1) {
				v = vArray[v].next[c];
				if(vArray[v].end != -1)
					result.push_back(make_pair(position, vArray[v].end));

				int curPrev = vArray[v].prevEnd;
				while(curPrev != -1) {
					result.push_back(make_pair(position, vArray[curPrev].end));
					curPrev = vArray[curPrev].prevEnd;
				}
				break;
			}
			if(v == 0 && vArray[v].next[c] == -1)
				break;
			v = vArray[v].link;
		}
	}
	return result;
}