#include"../../Graph_++11/Graph_++11/graph.h"
#include"../../SNM/SNM/SNM.h"
#include<iostream>
#include<vector>
#include<list>
#include<fstream>

void setColorWhite(Graph<int,int>& tree) {//paint in white(0)
	std::list<Vertex<int,int>> v = tree.allVertices();
	for(auto it = v.begin(); it != v.end(); ++it)
		tree.setVertexColor(it->No_of_vertex, 0);
}

void dfs(Graph<int,int>& tree, Graph<int,int>::MyIterator it, std::vector<std::pair<int,int> >& table, SNM::SetsSystem<int>& dsu, std::vector<SNM::Node<int>* >& dsu_map) {
	it.setVertexColor(1);
	dsu_map[it.getVertexNo()] = dsu.addSet(it.getVertexNo(),it.getVertexNo());
	while(!(it ==  tree.end(it.getVertexNo()))) {
		Graph<int, int>::MyIterator temp_it = it;
		temp_it.goForward();
		dfs(tree, temp_it, table, dsu, dsu_map);
		dsu.connectAtoB(dsu.find(dsu_map[temp_it.getVertexNo()]), dsu.find(dsu_map[it.getVertexNo()]));
		++it;
	}
	for(int i = 0; i < table.size(); ++i)
		if(table[i].first == it.getVertexNo() && tree.getVertexColor(table[i].second) == 2)
			std::cout << it.getVertexNo() << "-" << table[i].second << " " << dsu.find(dsu_map[table[i].second]) << std::endl;
		else
			if(table[i].second == it.getVertexNo() && tree.getVertexColor(table[i].first) == 2)
				std::cout << it.getVertexNo() << "-" << table[i].first << " " << dsu.find(dsu_map[table[i].first]) << std::endl;
	it.setVertexColor(2);
}

void DFS(Graph<int,int>& tree, std::vector<std::pair<int,int> >& table, int root, SNM::SetsSystem<int>& dsu, std::vector<SNM::Node<int>* >& dsu_map) {
	Graph<int, int>::MyIterator it = tree.begin(root);
	dfs(tree, it, table, dsu, dsu_map);
}

int main() {
	Graph<int, int> tree;
	std::ifstream in("input.txt");
	in >> tree;
	setColorWhite(tree);
	std::vector<std::pair<int,int> > table;
	int n;
	int root;
	in >> n >> root;
	for(int i = 0; i < n; ++i) {
		int x;
		int y;
		in >> x >> y;
		table.push_back(std::make_pair(x,y));
	}
	int n_size = tree.allVertices().size();
	SNM::SetsSystem<int> dsu;
	std::vector<SNM::Node<int>* > dsu_map(n_size + 1);
	DFS(tree, table, root, dsu, dsu_map);
	return 0;
}
