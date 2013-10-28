#ifndef _PREDPOTOK
#define _PREDPOTOK
#include"graph.h"
#include<list>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;

template<typename type_of_vertex_value>
int EstimateF(Graph<type_of_vertex_value, pair<int,int> >& ret_graph, int v) {
	int sum = 0;
	list<Edge<pair<int, int> > > out_e = ret_graph.getListOutEdges(v);
	for(auto i = out_e.begin(); i != out_e.end(); ++i)
		sum -= (i->weight).second;
	list<Edge<pair<int, int> > > in_e = ret_graph.getListInEdges(v);
	for(auto i = in_e.begin(); i != in_e.end(); ++i)
		sum += (i->weight).second;
	return sum;
}

template<typename type_of_vertex_value>
int FindChild(Graph<type_of_vertex_value, pair<int,int> >& ret_graph, int v) {
	int H = ret_graph.getVertexColor(v);
	list<Edge<pair<int, int> > > out_e = ret_graph.getListOutEdges(v);
	for(auto i = out_e.begin(); i != out_e.end(); ++i) {
		if(i->weight.first == i->weight.second)
			continue;
		int h = ret_graph.getVertexColor(i->to);
		if(h < H)
			return i->to;
	}
	list<Edge<pair<int, int> > > in_e = ret_graph.getListInEdges(v);
	for(auto i = in_e.begin(); i != in_e.end(); ++i) {
		if(i->weight.second == 0)
			continue;
		int h = ret_graph.getVertexColor(i->to);
		if(h < H)
			return -i->to;
	}
	return v;
}

template<typename type_of_vertex_value>
int Push(Graph<type_of_vertex_value, pair<int,int> >& ret_graph, int v) {
	int sum = EstimateF(ret_graph, v);
	if(sum == 0)
		return 0;
	int v_child = FindChild(ret_graph, v);
	if(v_child == v)
		return 0;
	if(v_child >= 0) {
		pair<int, int> edge_state = ret_graph.getEdgeWeight(v,v_child);
		int delta = min(sum, edge_state.first - edge_state.second);
		ret_graph.setEdgeWeight(v,v_child,make_pair(edge_state.first, edge_state.second + delta));
	} else {
		pair<int, int> edge_state = ret_graph.getEdgeWeight(-v_child,v);
		int delta = min(sum, edge_state.second);
		ret_graph.setEdgeWeight(-v_child,v,make_pair(edge_state.first, edge_state.second - delta));
	}
	//ret_graph.setEdgeWeight(v_child,v,make_pair(edge_state.first, -edge_state.second - delta));
	return 1;
}

template<typename type_of_vertex_value>
int Relabel(Graph<type_of_vertex_value, pair<int,int>>& ret_graph, int v) {
	int sum = EstimateF(ret_graph, v);
	if(sum == 0)
		return 0;
	int H = ret_graph.getVertexColor(v);
	int min = 100000;
	list<Edge<pair<int, int> > > out_e = ret_graph.getListOutEdges(v);
	for(auto i = out_e.begin(); i != out_e.end(); ++i) {
		if(i->weight.first == i->weight.second)
			continue;
		int h = ret_graph.getVertexColor(i->to);
		if(h < H)
			return 0;
		if(h < min)
			min = h;
	}
	list<Edge<pair<int, int> > > in_e = ret_graph.getListInEdges(v);
	for(auto i = in_e.begin(); i != in_e.end(); ++i) {
		if(i->weight.second == 0)
			continue;
		int h = ret_graph.getVertexColor(i->to);
		if(h < H)
			return 0;
		if(h < min)
			min = h;
	}
	ret_graph.setVertexColor(v, min + 1);
	return 1;
}

template<typename type_of_vertex_value>
Graph<type_of_vertex_value, pair<int,int> > Predpotok(const Graph<type_of_vertex_value, int>& cur_graph, int source, int target) {
	Graph<type_of_vertex_value, pair<int, int>> ret_graph(1);//first is c(e), second is f(e)

	auto list_vertices = cur_graph.allVertices();
	if(list_vertices.size() == 0)
		return nullptr;
	for(auto i = list_vertices.begin(); i != list_vertices.end(); ++i)
		ret_graph.addVertex(i->No_of_vertex, i->value);

	list<Edge<int> > list_edges = cur_graph.allEdges();
	if(list_edges.size() == 0)
		return nullptr;
	for(auto it = list_edges.begin(); it != list_edges.end(); ++it)
		ret_graph.addEdge(it->from, it->to, make_pair(it->weight, 0));
	
	for(Graph<type_of_vertex_value, pair<int,int> >::MyIterator it = ret_graph.begin(source);!(it == ret_graph.end(source)); ++it) {
		int temp_c = ret_graph.getEdgeWeight(source,it.getCurrentChildNo()).first;
		ret_graph.setEdgeWeight(source,it.getCurrentChildNo(), make_pair(temp_c, temp_c));
		//cout << ret_graph;
		//ret_graph.setEdgeWeight(it.getCurrentChildNo(), source, make_pair(temp_c, -temp_c));
		//cout << ret_graph;
	}

	for(auto i = list_vertices.begin(); i != list_vertices.end(); ++i)
		ret_graph.setVertexColor(i->No_of_vertex,0);
	ret_graph.setVertexColor(source, list_vertices.size());

	while(1) {
		int flag = 0;
		for(auto i = list_vertices.begin(); i != list_vertices.end(); ++i) {
			if(i->No_of_vertex != target && i->No_of_vertex != source) {
				flag += Push(ret_graph, i->No_of_vertex);
				flag += Relabel(ret_graph, i->No_of_vertex);
			}
		}
		//cout << ret_graph;
		if(flag == 0)
			break;
	}
	return ret_graph;
}

#endif