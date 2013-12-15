#include "Ukk.h"

using namespace std;

bool find(const SuffTree& tree, const string& str) {
	return 1;
}

vector<bool> Ukk(const vector<string>& needle, istream& in) {
	SuffTree tree;
	tree.init();

	unsigned int c;
	unsigned char cc;
	int index = 0;
	vector<unsigned int> text;
	while(in >> cc) {
		c = cc;
		text.push_back(c);
		while(1) {
			if(*(tree.nodes[tree.curNode].r) < tree.edgePos) {
				if(tree.nodes[tree.curNode].childs[c]  == -1) {
					tree.nodes[tree.curNode].childs[c] = tree.size;
					tree.nodes.resize(tree.size + 1);
					tree.nodes[tree.size].l = new int(index);
					tree.nodes[tree.size++].parent = tree.curNode;
					tree.curNode = tree.nodes[tree.curNode].link;
					tree.edgePos = *(tree.nodes[tree.curNode].r) + 1;
					continue;
				} else {
					tree.curNode = tree.nodes[tree.curNode].childs[c];
					tree.edgePos = *(tree.nodes[tree.curNode].l);
				}
			}
			if(tree.edgePos == -1 || c == text[tree.edgePos])
				++tree.edgePos;
			else {
				if(*(tree.nodes[tree.curNode].l) != tree.edgePos) {
					//----------split the edge
					tree.nodes.resize(tree.size + 2);
					tree.nodes[tree.size].l = tree.nodes[tree.curNode].l;
					tree.nodes[tree.size].r = new int(tree.edgePos - 1);
					tree.nodes[tree.size].parent = tree.nodes[tree.curNode].parent;
					tree.nodes[tree.size].childs[text[tree.edgePos]] = tree.curNode;
					//---------new list
					tree.nodes[tree.size].childs[c] = tree.size + 1;
					tree.nodes[tree.size + 1].l = new int(index);
					tree.nodes[tree.size + 1].parent = tree.size;
					//-----------the r-end
					tree.nodes[tree.curNode].l = new int(tree.edgePos);
					tree.nodes[tree.curNode].parent = tree.size;
					tree.nodes[tree.nodes[tree.size].parent].childs[text[*(tree.nodes[tree.size].l)]] =  tree.size;
					++tree.size;
					++tree.size;
					//------------begin linking
					tree.curNode = tree.nodes[tree.nodes[tree.size - 2].parent].link;
					tree.edgePos = *(tree.nodes[tree.size - 2].l);
					//---------linking(going through 0------(0)------(0)---0 <-here or --(0)--- <-here
					while(tree.edgePos <= *(tree.nodes[tree.size - 2].r)) {
							tree.curNode = tree.nodes[tree.curNode].childs[text[tree.edgePos]];
							tree.edgePos += *(tree.nodes[tree.curNode].r)-*(tree.nodes[tree.curNode].l)+1;
					}
					//-------make link
					if(tree.edgePos == *(tree.nodes[tree.size - 2].r)+1)
						tree.nodes[tree.size-2].link = tree.curNode;
					else
						tree.nodes[tree.size-2].link = tree.size;
					//-----continue
					tree.edgePos = *(tree.nodes[tree.curNode].r)-(tree.edgePos-*(tree.nodes[tree.size-2].r))+2;
					continue;
				} else {
					//----------add node
					tree.nodes.resize(tree.size + 1);
					//---------new list
					tree.nodes[tree.nodes[tree.curNode].parent].childs[c] = tree.size;
					tree.nodes[tree.size].l = new int(index);
					tree.nodes[tree.size].parent = tree.nodes[tree.curNode].parent;
					//-----------++size
					++tree.size;
					//------------begin linking
					tree.curNode = tree.nodes[tree.nodes[tree.size - 1].parent].link;
					tree.edgePos = *(tree.nodes[tree.size - 1].l);
					//---------linking(going through 0------(0)------(0)---0 <-here or --(0)--- <-here
					while(tree.edgePos <= *(tree.nodes[tree.size - 1].r)) {
							tree.curNode = tree.nodes[tree.curNode].childs[text[tree.edgePos]];
							tree.edgePos += *(tree.nodes[tree.curNode].r)-*(tree.nodes[tree.curNode].l)+1;
					}
					//-------make link
					if(tree.edgePos == *(tree.nodes[tree.size - 1].r)+1)
						tree.nodes[tree.size-1].link = tree.curNode;
					else
						tree.nodes[tree.size-1].link = tree.size;
					//-----continue
					tree.edgePos = *(tree.nodes[tree.curNode].r)-(tree.edgePos-*(tree.nodes[tree.size-1].r))+2;
					continue;
				}
			}
			break;
		}
	++index;
	}

	//--unique
	c = 256;
	while(1) {
		if(*(tree.nodes[tree.curNode].r) < tree.edgePos) {
			if(tree.nodes[tree.curNode].childs[c]  == -1) {
				tree.nodes[tree.curNode].childs[c] = tree.size;
				tree.nodes.resize(tree.size + 1);
				tree.nodes[tree.size].l = new int(index);
				tree.nodes[tree.size++].parent = tree.curNode;
				tree.curNode = tree.nodes[tree.curNode].link;
				tree.edgePos = *(tree.nodes[tree.curNode].r) + 1;
				continue;
			} else {
				tree.curNode = tree.nodes[tree.curNode].childs[c];
				tree.edgePos = *(tree.nodes[tree.curNode].l);
			}
		}
		if(tree.edgePos == -1 || c == text[tree.edgePos])
			++tree.edgePos;
		else {
			if(*(tree.nodes[tree.curNode].l) != tree.edgePos) {
				//----------split the edge
				tree.nodes.resize(tree.size + 2);
				tree.nodes[tree.size].l = tree.nodes[tree.curNode].l;
				tree.nodes[tree.size].r = new int(tree.edgePos - 1);
				tree.nodes[tree.size].parent = tree.nodes[tree.curNode].parent;
				tree.nodes[tree.size].childs[text[tree.edgePos]] = tree.curNode;
				//---------new list
				tree.nodes[tree.size].childs[c] = tree.size + 1;
				tree.nodes[tree.size + 1].l = new int(index);
				tree.nodes[tree.size + 1].parent = tree.size;
				//-----------the r-end
				tree.nodes[tree.curNode].l = new int(tree.edgePos);
				tree.nodes[tree.curNode].parent = tree.size;
				tree.nodes[tree.nodes[tree.size].parent].childs[text[*(tree.nodes[tree.size].l)]] =  tree.size;
				++tree.size;
				++tree.size;
				//------------begin linking
				tree.curNode = tree.nodes[tree.nodes[tree.size - 2].parent].link;
				tree.edgePos = *(tree.nodes[tree.size - 2].l);
				//---------linking(going through 0------(0)------(0)---0 <-here or --(0)--- <-here
				while(tree.edgePos <= *(tree.nodes[tree.size - 2].r)) {
						tree.curNode = tree.nodes[tree.curNode].childs[text[tree.edgePos]];
						tree.edgePos += *(tree.nodes[tree.curNode].r)-*(tree.nodes[tree.curNode].l)+1;
				}
				//-------make link
				if(tree.edgePos == *(tree.nodes[tree.size - 2].r)+1)
					tree.nodes[tree.size-2].link = tree.curNode;
				else
					tree.nodes[tree.size-2].link = tree.size;
				//-----continue
				tree.edgePos = *(tree.nodes[tree.curNode].r)-(tree.edgePos-*(tree.nodes[tree.size-2].r))+2;
				continue;
			} else {
				//----------add node
				tree.nodes.resize(tree.size + 1);
				//---------new list
				tree.nodes[tree.nodes[tree.curNode].parent].childs[c] = tree.size;
				tree.nodes[tree.size].l = new int(index);
				tree.nodes[tree.size].parent = tree.nodes[tree.curNode].parent;
				//-----------++size
				++tree.size;
				//------------begin linking
				tree.curNode = tree.nodes[tree.nodes[tree.size - 1].parent].link;
				tree.edgePos = *(tree.nodes[tree.size - 1].l);
				//---------linking(going through 0------(0)------(0)---0 <-here or --(0)--- <-here
				while(tree.edgePos <= *(tree.nodes[tree.size - 1].r)) {
						tree.curNode = tree.nodes[tree.curNode].childs[text[tree.edgePos]];
						tree.edgePos += *(tree.nodes[tree.curNode].r)-*(tree.nodes[tree.curNode].l)+1;
				}
				//-------make link
				if(tree.edgePos == *(tree.nodes[tree.size - 1].r)+1)
					tree.nodes[tree.size-1].link = tree.curNode;
				else
					tree.nodes[tree.size-1].link = tree.size;
				//-----continue
				tree.edgePos = *(tree.nodes[tree.curNode].r)-(tree.edgePos-*(tree.nodes[tree.size-1].r))+2;
				continue;
			}
		}
		break;
	}

	vector<bool> result;
	for(int i = 0; i < needle.size(); ++i)
		result.push_back(find(tree, needle[i]));

	return result;
}