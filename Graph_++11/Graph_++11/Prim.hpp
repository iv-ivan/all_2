#ifndef _PRIM
#define _PRIM
#include"../../BinomHeap/BinomHeap/BinomHeap.h"
#include"graph.h"
#include<list>
#include<unordered_set>
using namespace std;

namespace Prim_ns { 
template<typename type_of_vertex_value, typename type_of_edge_weight>
	void setColorToWhite(Graph<type_of_vertex_value, type_of_edge_weight>& current_graph) {
		auto vertices(current_graph.allVertices());
	
		for(auto iterator_vertices = vertices.begin(); iterator_vertices != vertices.end(); ++iterator_vertices)
			current_graph.setVertexColor(iterator_vertices->No_of_vertex, 0);
	}
}

template<typename type_of_edge_weight>
struct weight_vertex {
	type_of_edge_weight w;
	int v_to;
	int v_from;
	bool operator < (const weight_vertex<type_of_edge_weight>& val) {
		return w < val.w;
	}
	bool operator <= (const weight_vertex<type_of_edge_weight>& val) {
		return w <= val.w;
	}
	weight_vertex(int z) {
		w = z;
		v_to = -1;
		v_from = -1;
	}
	weight_vertex():v_to(-1),v_from(-1),w(-1){};
	void operator =(const weight_vertex<type_of_edge_weight>& val) {
		w = val.w;
		if(val.v_to != -1)
			v_to = val.v_to;
		if(val.v_from != -1)
			v_from = val.v_from;
	}
	weight_vertex (const weight_vertex<type_of_edge_weight>& val) {
		w = val.w;
		if(val.v_to != -1)
			v_to = val.v_to;
		if(val.v_from != -1)
			v_from = val.v_from;
	}
};

//template<typename type_of_vertex_value, typename type_of_edge_weight>
//Graph<type_of_vertex_value, type_of_edge_weight> Prim(Graph<type_of_vertex_value, type_of_edge_weight> cur_graph) {
//	Prim_ns::setColorToWhite(cur_graph);
//	Graph<type_of_vertex_value, type_of_edge_weight> ret_graph;
//
//	auto list_vertices = cur_graph.allVertices();
//	if(list_vertices.size() == 0)
//		return nullptr;
//	for(auto i = list_vertices.begin(); i != list_vertices.end(); ++i)
//		ret_graph.addVertex(i->No_of_vertex, i->value);
//
//	int v0 = list_vertices.begin()->No_of_vertex;
//	BinomHeap<weight_vertex<type_of_edge_weight>> cut;
//	cur_graph.setVertexColor(v0, 1);
//	int size_of_tree = 1;
//	for(auto it = list_vertices.begin()->out_edges.begin(); it != list_vertices.begin()->out_edges.end(); ++it) {
//		weight_vertex<type_of_edge_weight> temp;
//		temp.v_to = it->to;
//		temp.v_from = it->from;
//		temp.w = it->weight;
//		cut.push(temp);
//	}
//
//	while(size_of_tree < list_vertices.size()) {
//		connectToTree(cur_graph, cut, ret_graph);
//		++size_of_tree;
//	}
//	return ret_graph;
//}

template<typename type_of_vertex_value, typename type_of_edge_weight>
Graph<type_of_vertex_value, type_of_edge_weight> Prim(Graph<type_of_vertex_value, type_of_edge_weight>& cur_graph) {
	Graph<type_of_vertex_value, type_of_edge_weight> ret_graph(0);

	auto list_vertices = cur_graph.allVertices();
	if(list_vertices.size() == 0)
		return nullptr;
	for(auto i = list_vertices.begin(); i != list_vertices.end(); ++i)
		ret_graph.addVertex(i->No_of_vertex, i->value);

	Prim_ns::setColorToWhite(ret_graph);
	int v0 = list_vertices.begin()->No_of_vertex;
	BinomHeap<weight_vertex<type_of_edge_weight>> cut;
	ret_graph.setVertexColor(v0, 1);
	int size_of_tree = 1;
	for(auto it = list_vertices.begin()->out_edges.begin(); it != list_vertices.begin()->out_edges.end(); ++it) {
		weight_vertex<type_of_edge_weight> temp;
		temp.v_to = it->to;
		temp.v_from = it->from;
		temp.w = it->weight;
		cut.push(temp);
	}

	while(size_of_tree < list_vertices.size()) {
		connectToTree(cur_graph, cut, ret_graph);
		++size_of_tree;
	}
	Prim_ns::setColorToWhite(ret_graph);
	return ret_graph;
}

template<typename type_of_vertex_value, typename type_of_edge_weight>
void connectToTree(Graph<type_of_vertex_value, type_of_edge_weight>& cur_graph, BinomHeap<weight_vertex<type_of_edge_weight>>& cut, Graph<type_of_vertex_value, type_of_edge_weight>& ret_graph) {
	weight_vertex<type_of_edge_weight> temp;
	do {
		temp = cut.top();
		cut.pop();
	} while(ret_graph.getVertexColor(temp.v_to) == 1);
	ret_graph.setVertexColor(temp.v_to, 1);
	ret_graph.addEdge(temp.v_from, temp.v_to, temp.w);
	//ret_graph.addEdge(temp.v_to, temp.v_from, temp.w);

	auto list_edges = cur_graph.getListOutEdges(temp.v_to);
	for(auto it = list_edges.begin(); it != list_edges.end(); ++it)
		if(ret_graph.getVertexColor(it->to) == 0) {
			weight_vertex<type_of_edge_weight> temp;
			temp.w = it->weight;
			temp.v_from = it->from;
			temp.v_to = it->to;
			cut.push(temp);
		}
}
#endif