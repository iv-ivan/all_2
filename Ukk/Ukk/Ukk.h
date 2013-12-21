#include <vector>
#include <string>
#include <unordered_set>
#include <list>

using namespace std;

struct Node {
	int childs[257];
	int* l;
	int* r;
	unsigned int parent;
	unsigned int link;
	Node() {
		for(int i = 0; i < 257; ++i)
			childs[i] = -1;
		r = new int(10000000);
	}
	list<int> posLeaves;
};

struct SuffTree {
	vector<Node> nodes;
	unsigned int curNode;
	int edgePos;//from curNode.l to curNode.r || -1 if no edges
	unsigned int size;

	int index;//char in text
	vector<unsigned int> text;

	void init(){
		index = 0;
		size = 2;
		curNode = 0;
		edgePos = 0;
		nodes.resize(2);
		for(int i = 0; i < 257; ++i)
			nodes[1].childs[i] = 0;
		nodes[0].link = 1;
		nodes[0].l = new int(-1);
		nodes[0].r = new int(-1);
		nodes[1].l = new int(-1);
		nodes[1].r = new int(-1);
	}
	void addChar(unsigned int);
	~SuffTree();
	/*bool*/list<int> find(const string& a);
	list<int> dfs(int curV,int prevL);
};

bool find(const SuffTree& tree, const string& str);
/*vector<bool>*/vector<list<int> > Ukk(const vector<string>& needle, istream& in);