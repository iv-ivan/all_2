#include "Ukk.h"

using namespace std;

bool find(const SuffTree& tree, const string& str) {
	return 1;
}

void SuffTree::addChar(unsigned int c) {
	text.push_back(c);
		while(1) {
			if(*(nodes[curNode].r) < edgePos) {
				if(nodes[curNode].childs[c]  == -1) {
					nodes[curNode].childs[c] = size;
					nodes.resize(size + 1);
					nodes[size].l = new int(index);
					nodes[size++].parent = curNode;
					curNode = nodes[curNode].link;
					edgePos = *(nodes[curNode].r) + 1;
					continue;
				} else {
					curNode = nodes[curNode].childs[c];
					edgePos = *(nodes[curNode].l);
				}
			}
			if(edgePos == -1 || c == text[edgePos])
				++edgePos;
			else {
				//----------split the edge
				nodes.resize(size + 2);
				nodes[size].l = nodes[curNode].l;
				nodes[size].r = new int(edgePos - 1);
				nodes[size].parent = nodes[curNode].parent;
				nodes[size].childs[text[edgePos]] = curNode;
				//---------new list
				nodes[size].childs[c] = size + 1;
				nodes[size + 1].l = new int(index);
				nodes[size + 1].parent = size;
				//-----------the r-end
				nodes[curNode].l = new int(edgePos);
				nodes[curNode].parent = size;
				nodes[nodes[size].parent].childs[text[*(nodes[size].l)]] =  size;
				++size;
				++size;
				//------------begin linking
				curNode = nodes[nodes[size - 2].parent].link;
				edgePos = *(nodes[size - 2].l);
				//---------linking(going through 0------(0)------(0)---0 <-here or --(0)--- <-here
				while(edgePos <= *(nodes[size - 2].r)) {
						curNode = nodes[curNode].childs[text[edgePos]];
						edgePos += *(nodes[curNode].r)-*(nodes[curNode].l)+1;
				}
				//-------make link
				if(edgePos == *(nodes[size - 2].r)+1)
					nodes[size-2].link = curNode;
				else
					nodes[size-2].link = size;
				//-----continue
				edgePos = *(nodes[curNode].r)-(edgePos-*(nodes[size-2].r))+2;
				continue;
			}
			break;
		}
	++index;
}

SuffTree::~SuffTree() {
	unordered_set<int*> borders;
	for(int i = 0; i < nodes.size(); ++i) {
		borders.insert(nodes[i].l);
		borders.insert(nodes[i].r);
	}
	for(auto i = borders.begin(); i != borders.end(); ++i)
		delete *i;
}

list<int> SuffTree::find(const string& a) {
	int curNode = 0;
	int l = -1;
	int r = -1;
	int posEdge = 0;
	for(int i = 0; i < a.size(); ++i) {
		if(posEdge > r)
			if(nodes[curNode].childs[a[i]] == -1) {
				list<int> res;
				return res;
			} else {
				curNode = nodes[curNode].childs[a[i]];
				l = *nodes[curNode].l;
				r = *nodes[curNode].r;
				posEdge = l;
				++posEdge;
			}
		else {
			if(text[posEdge] == a[i])
				++posEdge;
			else {
				list<int> res;
				return res;
			}
		}
	}
	return nodes[curNode].posLeaves;
}

list<int> SuffTree::dfs(int curV, int prevL) {
	bool isLeaf = true;
	for(int i = 0; i < 256; ++i)
		if(nodes[curV].childs[i] != -1) {
			int v = nodes[curV].childs[i];
			isLeaf = false;
			list<int> temp;
			if(*(nodes[v].r) != 10000000)
				 temp = dfs(v,prevL+*(nodes[v].r)-*(nodes[v].l)+1);
			else
				temp = dfs(v,prevL+text.size()-*(nodes[v].l)+1);
			nodes[curV].posLeaves.splice(nodes[curV].posLeaves.begin(),temp);
		}

	if(isLeaf) {
		list<int> res;
		res.push_back(text.size()-prevL);
		nodes[curV].posLeaves = res;
		return res;
	}
	return nodes[curV].posLeaves;
}



/*vector<bool>*/vector<list<int> > Ukk(const vector<string>& needle, istream& in) {
	SuffTree tree;
	tree.init();

	unsigned char cc;
	while(in >> cc)
		tree.addChar(cc);

	//--unique
	//c = 256;
	//while(1) {
	//	if(*(tree.nodes[tree.curNode].r) < tree.edgePos) {
	//		if(tree.nodes[tree.curNode].childs[c]  == -1) {
	//			tree.nodes[tree.curNode].childs[c] = tree.size;
	//			tree.nodes.resize(tree.size + 1);
	//			tree.nodes[tree.size].l = new int(index);
	//			tree.nodes[tree.size++].parent = tree.curNode;
	//			tree.curNode = tree.nodes[tree.curNode].link;
	//			tree.edgePos = *(tree.nodes[tree.curNode].r) + 1;
	//			continue;
	//		} else {
	//			tree.curNode = tree.nodes[tree.curNode].childs[c];
	//			tree.edgePos = *(tree.nodes[tree.curNode].l);
	//		}
	//	}
	//	if(tree.edgePos == -1 || c == text[tree.edgePos])
	//		++tree.edgePos;
	//	else {
	//		//----------split the edge
	//		tree.nodes.resize(tree.size + 2);
	//		tree.nodes[tree.size].l = tree.nodes[tree.curNode].l;
	//		tree.nodes[tree.size].r = new int(tree.edgePos - 1);
	//		tree.nodes[tree.size].parent = tree.nodes[tree.curNode].parent;
	//		tree.nodes[tree.size].childs[text[tree.edgePos]] = tree.curNode;
	//		//---------new list
	//		tree.nodes[tree.size].childs[c] = tree.size + 1;
	//		tree.nodes[tree.size + 1].l = new int(index);
	//		tree.nodes[tree.size + 1].parent = tree.size;
	//		//-----------the r-end
	//		tree.nodes[tree.curNode].l = new int(tree.edgePos);
	//		tree.nodes[tree.curNode].parent = tree.size;
	//		tree.nodes[tree.nodes[tree.size].parent].childs[text[*(tree.nodes[tree.size].l)]] =  tree.size;
	//		++tree.size;
	//		++tree.size;
	//		//------------begin linking
	//		tree.curNode = tree.nodes[tree.nodes[tree.size - 2].parent].link;
	//		tree.edgePos = *(tree.nodes[tree.size - 2].l);
	//		//---------linking(going through 0------(0)------(0)---0 <-here or --(0)--- <-here
	//		while(tree.edgePos <= *(tree.nodes[tree.size - 2].r)) {
	//				tree.curNode = tree.nodes[tree.curNode].childs[text[tree.edgePos]];
	//				tree.edgePos += *(tree.nodes[tree.curNode].r)-*(tree.nodes[tree.curNode].l)+1;
	//		}
	//		//-------make link
	//		if(tree.edgePos == *(tree.nodes[tree.size - 2].r)+1)
	//			tree.nodes[tree.size-2].link = tree.curNode;
	//		else
	//			tree.nodes[tree.size-2].link = tree.size;
	//		//-----continue
	//		tree.edgePos = *(tree.nodes[tree.curNode].r)-(tree.edgePos-*(tree.nodes[tree.size-2].r))+2;
	//		continue;
	//	}
	//	break;
	//}
	tree.dfs(0,-1);
	/*vector<bool> result;
	for(int i = 0; i < needle.size(); ++i)
		result.push_back(tree.find(needle[i]));*/
	vector<list<int> > result;
	for(int i = 0; i < needle.size(); ++i)
		result.push_back(tree.find(needle[i]));
	return result;
}