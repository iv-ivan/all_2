#ifndef _KRUS
#define _KRUS
#include"../../SNM/SNM/SNM.h"
#include"graph.h"
#include<list>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;

template<typename type_of_edge_weight>
bool comparator(Edge<type_of_edge_weight>& e_1, Edge<type_of_edge_weight>& e_2) {
	return e_1.weight < e_2.weight;
}

template<typename type_of_vertex_value, typename type_of_edge_weight>
Graph<type_of_vertex_value, type_of_edge_weight> Kruskal(Graph<type_of_vertex_value, type_of_edge_weight>& cur_graph) {
	Graph<type_of_vertex_value, type_of_edge_weight> ret_graph;

	auto list_vertices = cur_graph.allVertices();
	SNM::SetsSystem<int> trees;
	unordered_map<int, SNM::Node<int>* > map_ptrs;
	if(list_vertices.size() == 0)
		return nullptr;
	for(auto i = list_vertices.begin(); i != list_vertices.end(); ++i) {
		ret_graph.addVertex(i->No_of_vertex, i->value);
		map_ptrs.insert(make_pair(i->No_of_vertex, trees.addSet(i->No_of_vertex,i->No_of_vertex)));
	}

	auto list_edges = cur_graph.allEdges();
	vector<Edge<type_of_edge_weight> > vector_edges(list_edges.begin(), list_edges.end());
	std::sort(vector_edges.begin(), vector_edges.end(), comparator<type_of_edge_weight>);

	int i0 = 0;
	while(trees.getNumOfSets() > 1) {
		for(int i = i0; i < vector_edges.size(); ++i) {
			int out = trees.find(map_ptrs[vector_edges[i].from]);
			int in = trees.find(map_ptrs[vector_edges[i].to]);
			if(in != out) {
				ret_graph.addEdge(vector_edges[i].from, vector_edges[i].to, vector_edges[i].weight);
				ret_graph.addEdge(vector_edges[i].to, vector_edges[i].from, vector_edges[i].weight);
				i0 = i+1;
				trees.connectAtoB(out,in);
				break;
			}
		}
	}
	return ret_graph;
}	
#endif