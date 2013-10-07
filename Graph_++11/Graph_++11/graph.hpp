#ifndef _GRAPH_HPP
#define _GRAPH_HPP
#include<iostream>
using namespace std;
#include"graph.h"
template<typename type_of_vertex_value, typename type_of_edge_weight> 
Vertex<type_of_vertex_value, type_of_edge_weight>::Vertex(): No_of_vertex(0), color(0), value(0), out_edges(), in_edges() {//конструктор по умолчанию
}

template<typename type_of_vertex_value, typename type_of_edge_weight> 
Vertex<type_of_vertex_value, type_of_edge_weight>::Vertex(int No): No_of_vertex(No), color(0), value(0), out_edges(), in_edges() {//конструктор по умолчанию
}

template<typename type_of_edge_weight> 
Edge<type_of_edge_weight>::Edge(): from(0), to(0), color(0), weight(0) {//конструктор по умолчанию
}

template<typename type_of_edge_weight> 
Edge<type_of_edge_weight>::Edge(const Edge<type_of_edge_weight>& copy_edge): from(copy_edge.from), to(copy_edge.to), color(copy_edge.color), weight(copy_edge.weight) {
}

template<typename type_of_vertex_value, typename type_of_edge_weight> 
Vertex<type_of_vertex_value, type_of_edge_weight>::Vertex(const Vertex<type_of_vertex_value, type_of_edge_weight>& copy_vertex): No_of_vertex(copy_vertex.No_of_vertex), color(copy_vertex.color), value(copy_vertex.value), out_edges(copy_vertex.out_edges), in_edges(copy_vertex.in_edges) {//конструктор по умолчанию
}

template<typename type_of_vertex_value, typename type_of_edge_weight> 
void Vertex<type_of_vertex_value, type_of_edge_weight>::operator =(const Vertex<type_of_vertex_value, type_of_edge_weight>& second) {
	 No_of_vertex = second.No_of_vertex;
	 color = second.color;
	 value = second.value;
	 out_edges = second.out_edges;
	 in_edges = second.in_edges;
}

template<typename type_of_edge_weight> 
void Edge<type_of_edge_weight>::operator =(const Edge<type_of_edge_weight>& second) {
	from = second.from;
	to = second.to;
	color = second.color;
	weight = second.weight;
}

template<typename type_of_vertex_value, typename type_of_edge_weight>
ostream& operator <<(ostream& out, const Vertex<type_of_vertex_value, type_of_edge_weight>& current_vertex) {
	out << "No_of_vertex: " << current_vertex.No_of_vertex << endl << "color:" << current_vertex.color << endl << "value: " << current_vertex.value << endl;
	out << "in_edges:" << endl;
	for(auto iterator_edge = current_vertex.in_edges.begin(); iterator_edge != current_vertex.in_edges.end(); ++iterator_edge) {
		out << *iterator_edge;
	}
	out << "out_edges:" << endl;
	for(auto iterator_edge = current_vertex.out_edges.begin(); iterator_edge != current_vertex.out_edges.end(); ++iterator_edge) {
		out << *iterator_edge;
	}
	return out;
}

template<typename type_of_vertex_value, typename type_of_edge_weight>
istream& operator >>(istream& in, Graph<type_of_vertex_value, type_of_edge_weight>& current_graph) {
	int v;//количество вершин
	cout << "number of vertices: ";
	in >> v;
	int n;//ребра
	cout << "number of edges: ";
	in >> n;
	cout << "enter vertices (No_of_vertex, val): " << endl;
	for(int i = 0; i < v; ++i) {
		int No;
		type_of_vertex_value val;
		in >> No;
		in >> val;
		current_graph.addVertex(No , val);
	}
	cout << "enter edges (from, to, weight): " << endl;
	for(int i = 0; i < n; ++i) {
		int from, to;
		type_of_edge_weight wei;
		in >> from >> to >> wei;
		current_graph.addEdge(from, to, wei);
	}
	return in;
}

template<typename type_of_vertex_value, typename type_of_edge_weight>
ostream& operator <<(ostream& out, const Graph<type_of_vertex_value, type_of_edge_weight>& current_graph) {
	for(auto iterator_vertex = current_graph.table_.begin(); iterator_vertex != current_graph.table_.end(); ++iterator_vertex)
		out << *(iterator_vertex->second) << endl;
	return out;
}

template<typename type_of_edge_weight>
ostream& operator <<(ostream& out, const Edge<type_of_edge_weight>& edge) {
	out << edge.from << " " << edge.to << " color: " << edge.color << " weight: " << edge.weight << endl;
	return out;
}


template<typename type_of_vertex_value, typename type_of_edge_weight>
bool Vertex<type_of_vertex_value, type_of_edge_weight>::operator >(const Vertex<type_of_vertex_value, type_of_edge_weight>& vertex) const {
	if(No_of_vertex > vertex.No_of_vertex)
		return 1;
	else return 0;
}

template<typename type_of_vertex_value, typename type_of_edge_weight>
bool Vertex<type_of_vertex_value, type_of_edge_weight>::operator <(const Vertex<type_of_vertex_value, type_of_edge_weight>& vertex) const {
	return vertex > *this;
}

template<typename type_of_vertex_value, typename type_of_edge_weight>
bool Vertex<type_of_vertex_value, type_of_edge_weight>::operator ==(const Vertex<type_of_vertex_value, type_of_edge_weight>& vertex) const {
	if(No_of_vertex == vertex.No_of_vertex)
		return 1;
	else return 0;
}

template<typename type_of_vertex_value, typename type_of_edge_weight>
bool Vertex<type_of_vertex_value, type_of_edge_weight>::operator >=(const Vertex<type_of_vertex_value, type_of_edge_weight>& vertex) const {
	if(No_of_vertex >= vertex.No_of_vertex)
		return 1;
	else return 0;
}

template<typename type_of_vertex_value, typename type_of_edge_weight>
bool Vertex<type_of_vertex_value, type_of_edge_weight>::operator <=(const Vertex<type_of_vertex_value, type_of_edge_weight>& vertex) const {
	return vertex >= *this;
}
//template<typename type_of_vertex_value, typename type_of_edge_weight>
//class graph {
//private:
//	bool orientation;//1 - ориентированный, 0 - неориентированный
//	vector<vertex<type_of_vertex_value, type_of_edge_weight> > table;//таблица вершина - индекс вектора, в паре - сосед, ребро
//public:
template<typename type_of_vertex_value, typename type_of_edge_weight>
Graph<type_of_vertex_value, type_of_edge_weight>::Graph():orientation_(1), table_() {//конструктор по умолчанию
}

template<typename type_of_vertex_value, typename type_of_edge_weight>
Graph<type_of_vertex_value, type_of_edge_weight>::Graph(const bool& or):orientation_(or), table_() {//конструктор ор./неор.
}

template<typename type_of_vertex_value, typename type_of_edge_weight>
Graph<type_of_vertex_value, type_of_edge_weight>::Graph(const Graph<type_of_vertex_value, type_of_edge_weight>& obj):orientation_(1) {//конструктор копирования
	for(auto iterator_vertex = obj.table_.begin(); iterator_vertex != obj.table_.end(); ++iterator_vertex) {
		addVertex(iterator_vertex->second->No_of_vertex,iterator_vertex->second->value);
		setVertexColor(iterator_vertex->second->No_of_vertex,iterator_vertex->second->color);
	}
	for(auto iterator_vertex = obj.table_.begin(); iterator_vertex != obj.table_.end(); ++iterator_vertex)
		for(auto iterator_edge = iterator_vertex->second->out_edges.begin(); iterator_edge != iterator_vertex->second->out_edges.end();++iterator_edge)
			addEdge(iterator_edge->from, iterator_edge->to, iterator_edge->weight);
	orientation_ = obj.orientation_;
}

template<typename type_of_vertex_value, typename type_of_edge_weight>
void Graph<type_of_vertex_value, type_of_edge_weight>::operator =(const Graph<type_of_vertex_value, type_of_edge_weight>& obj) {//присваивание
	orientation_ = obj.orientation_;
	table_ = obj.table_;
}

template<typename type_of_vertex_value, typename type_of_edge_weight>
bool Graph<type_of_vertex_value, type_of_edge_weight>::operator ==(const Graph<type_of_vertex_value, type_of_edge_weight>& obj) const {//проверка на равенство
	return ((orientation_ == obj.orientation_) && (table_ == obj.table_));
}

template<typename type_of_vertex_value, typename type_of_edge_weight>
void Graph<type_of_vertex_value, type_of_edge_weight>::addVertex(int No, const type_of_vertex_value& val) {//добавить не связанную ни с кем вершину
	Vertex<type_of_vertex_value, type_of_edge_weight>* new_vertex = new Vertex<type_of_vertex_value, type_of_edge_weight>;
	new_vertex->No_of_vertex = No;
	new_vertex->value = val;
	unique_ptr<Vertex<type_of_vertex_value, type_of_edge_weight> > ptr_new_vertex(new_vertex);
	table_.insert(make_pair(No, move(ptr_new_vertex)));
}

template<typename type_of_vertex_value, typename type_of_edge_weight>
void Graph<type_of_vertex_value, type_of_edge_weight>::addEdgeSafe(int from, int to, const type_of_edge_weight& weight) {//добавит ребро, предотвращая зацикливаниеа
	Edge<type_of_edge_weight> temp;
	temp.from = from;
	temp.to = to;
	temp.weight = weight;
	auto table_iterator = table_.find(from);
	table_iterator->second->out_edges.push_back(temp);

	temp.from = to;
	temp.to = from;
	table_iterator = table_.find(to);
	table_iterator->second->in_edges.push_back(temp);
}

template<typename type_of_vertex_value, typename type_of_edge_weight>
void Graph<type_of_vertex_value, type_of_edge_weight>::addEdge(int from, int to, const type_of_edge_weight& weight) {//добавит ребро
	addEdgeSafe(from,to,weight);
	if(orientation_ == 0)
		addEdgeSafe(to,from,weight);
}

template<typename type_of_vertex_value, typename type_of_edge_weight>
void Graph<type_of_vertex_value, type_of_edge_weight>::deleteVertex(int No_of_vertex) {//добавить не связанную ни с кем вершину
	auto iterator_vertex = table_.find(No_of_vertex);
	//for(auto temp_iterator = iterator_vertex->second->in_edges.begin(); temp_iterator != iterator_vertex->second->in_edges.end(); ++temp_iterator)
	while(iterator_vertex->second->in_edges.size() != 0)
		deleteEdge(iterator_vertex->second->in_edges.begin()->to, iterator_vertex->second->in_edges.begin()->from);
	//for(auto temp_iterator = iterator_vertex->second->out_edges.begin(); temp_iterator != iterator_vertex->second->out_edges.end(); ++temp_iterator)
		//deleteEdge(temp_iterator->from, temp_iterator->to);
	while(iterator_vertex->second->out_edges.size() != 0)
		deleteEdge(iterator_vertex->second->out_edges.begin()->from, iterator_vertex->second->out_edges.begin()->to);
	table_.erase(No_of_vertex);
}

template<typename type_of_vertex_value, typename type_of_edge_weight>
void Graph<type_of_vertex_value, type_of_edge_weight>::deleteEdgeSafe(int from, int to) {//удалвит ребро
	auto iterator_vertex_from = table_.find(from);
	for(auto temp_iterator = iterator_vertex_from->second->out_edges.begin(); temp_iterator != iterator_vertex_from->second->out_edges.end(); ++temp_iterator) {
		if(temp_iterator->to == to) {
			iterator_vertex_from->second->out_edges.erase(temp_iterator);
			break;
		}
	}

	iterator_vertex_from = table_.find(to);
	for(auto temp_iterator = iterator_vertex_from->second->in_edges.begin(); temp_iterator != iterator_vertex_from->second->in_edges.end(); ++temp_iterator) {
		if(temp_iterator->to == from) {
			iterator_vertex_from->second->in_edges.erase(temp_iterator);
			break;
		}
	}
}

template<typename type_of_vertex_value, typename type_of_edge_weight>
void Graph<type_of_vertex_value, type_of_edge_weight>::deleteEdge(int from, int to) {//удалвит ребро
	deleteEdgeSafe(from, to);
	if(orientation_ == 0)
		deleteEdgeSafe(to,from);
}

template<typename type_of_vertex_value, typename type_of_edge_weight>
void Graph<type_of_vertex_value, type_of_edge_weight>::transpose() {//транспонировать
	list<Edge<type_of_edge_weight> > temp_edges;
	for(auto temp_iterator = table_.begin(); temp_iterator != table_.end(); ++temp_iterator) {
		temp_edges = temp_iterator->second->out_edges;
		temp_iterator->second->out_edges = temp_iterator->second->in_edges;
		temp_iterator->second->in_edges = temp_edges;
	}
}

//template<typename type_of_edge_weight0>
template<typename type_of_vertex_value, typename type_of_edge_weight>
list<Edge<type_of_edge_weight> > Graph<type_of_vertex_value, type_of_edge_weight>::getListOutEdges(int No_of_vertex) const {
	auto iterator_vertex = table_.find(No_of_vertex);
	return iterator_vertex->second->out_edges;
}

template<typename type_of_vertex_value, typename type_of_edge_weight>
list<Vertex<type_of_vertex_value, type_of_edge_weight> > Graph<type_of_vertex_value, type_of_edge_weight>::getListChildren(int No_of_vertex) const {
	list<Vertex<type_of_vertex_value, type_of_edge_weight> > temp;
	auto iterator_vertex = table_.find(No_of_vertex);
	for(auto iterator_edge = iterator_vertex->second->out_edges.begin(); iterator_edge != iterator_vertex->second->out_edges.end(); ++iterator_edge)
		temp.push_back(*((table_.find(iterator_edge->to))->second));
	return temp;
}

//template<typename type_of_edge_weight0>
template<typename type_of_vertex_value, typename type_of_edge_weight>
list<Edge<type_of_edge_weight> > Graph<type_of_vertex_value, type_of_edge_weight>::getListInEdges(int No_of_vertex) const {//список ребер в вершину
	auto iterator_vertex = table_.find(No_of_vertex);
	return iterator_vertex->second->in_edges;
}

template<typename type_of_vertex_value, typename type_of_edge_weight>
list<Vertex<type_of_vertex_value, type_of_edge_weight> > Graph<type_of_vertex_value, type_of_edge_weight>::getListParents(int No_of_vertex) const {//список соседних вершин, из которых ведет к нам
	list<Vertex<type_of_vertex_value, type_of_edge_weight> > temp;
	auto iterator_vertex = table_.find(No_of_vertex);
	for(auto iterator_edge = iterator_vertex->second->in_edges.begin(); iterator_edge != iterator_vertex->second->in_edges.end(); ++iterator_edge)
		temp.push_back(*((table_.find(iterator_edge->to))->second));
	return temp;
}

template<typename type_of_vertex_value, typename type_of_edge_weight>
list<Vertex<type_of_vertex_value, type_of_edge_weight> > Graph<type_of_vertex_value, type_of_edge_weight>::allVertices() const {//список всех вершин
	list<Vertex<type_of_vertex_value, type_of_edge_weight> > temp;
	for(auto iterator_vertex = table_.begin(); iterator_vertex != table_.end(); ++iterator_vertex)
		temp.push_back(*(iterator_vertex->second));
	return temp;
}

//template<typename type_of_edge_weight>
template<typename type_of_vertex_value, typename type_of_edge_weight>
list<Edge<type_of_edge_weight> > Graph<type_of_vertex_value, type_of_edge_weight>::allEdges() const {//список всех ребер
	list<Edge<type_of_edge_weight> > temp;
	for(auto iterator_vertex = table_.begin(); iterator_vertex != table_.end(); ++iterator_vertex)
		for(auto iterator_edge = iterator_vertex->second->out_edges.begin(); iterator_edge != iterator_vertex->second->out_edges.end(); ++iterator_edge)
			temp.push_back(*iterator_edge);
	return temp;
}

template<typename type_of_vertex_value, typename type_of_edge_weight>
type_of_vertex_value Graph<type_of_vertex_value, type_of_edge_weight>::getVertexValue(int No_of_vertex) const {//получить то, что хранится
	auto iterator_vertex = table_.find(No_of_vertex);
	return iterator_vertex->second->value;
}

template<typename type_of_vertex_value, typename type_of_edge_weight>
void Graph<type_of_vertex_value, type_of_edge_weight>::setVertexValue(int No_of_vertex, const type_of_vertex_value& value) {//изменить то, что хранится
	auto iterator_vertex = table_.find(No_of_vertex);
	iterator_vertex->second->value = value;
}

template<typename type_of_vertex_value, typename type_of_edge_weight>
int Graph<type_of_vertex_value, type_of_edge_weight>::getVertexColor(int No_of_vertex) const {//получить цвет
	auto iterator_vertex = table_.find(No_of_vertex);
	return iterator_vertex->second->color;
}

template<typename type_of_vertex_value, typename type_of_edge_weight>
void Graph<type_of_vertex_value, type_of_edge_weight>::setVertexColor(int No_of_vertex, int new_color) {//получить цвет
	auto iterator_vertex = table_.find(No_of_vertex);
	iterator_vertex->second->color = new_color;
}

template<typename type_of_vertex_value, typename type_of_edge_weight>
int Graph<type_of_vertex_value, type_of_edge_weight>::getEdgeColor(int from, int to) const {//получить уцвет
	auto iterator_vertex = table_.find(from);
	for(auto iterator_edge = iterator_vertex->second->out_edges.begin(); iterator_edge != iterator_vertex->second->out_edges.end(); ++iterator_edge)
		if(iterator_edge->to == to)
			return iterator_edge->color;
	return 0;
}

template<typename type_of_vertex_value, typename type_of_edge_weight>
void Graph<type_of_vertex_value, type_of_edge_weight>::setEdgeColor(int from, int to, int new_color) {//выставить цвет
	auto iterator_vertex = table_.find(from);
	for(auto iterator_edge = iterator_vertex->second->out_edges.begin(); iterator_edge != iterator_vertex->second->out_edges.end(); ++iterator_edge)
		if(iterator_edge->to == to) {
			iterator_edge->color = new_color;
			break;
		}
	iterator_vertex = table_.find(to);
	for(auto iterator_edge = iterator_vertex->second->in_edges.begin(); iterator_edge != iterator_vertex->second->in_edges.end(); ++iterator_edge)
		if(iterator_edge->to == from) {
			iterator_edge->color = new_color;
			break;
		}
}

template<typename type_of_vertex_value, typename type_of_edge_weight>
type_of_edge_weight Graph<type_of_vertex_value, type_of_edge_weight>::getEdgeWeight(int from, int to) const {//получить вес
	auto iterator_vertex = table_.find(from);
	for(auto iterator_edge = iterator_vertex->second->out_edges.begin(); iterator_edge != iterator_vertex->second->out_edges.end(); ++iterator_edge)
		if(iterator_edge->to == to)
			return iterator_edge->weight;
	return 10000000;
}

template<typename type_of_vertex_value, typename type_of_edge_weight>
void Graph<type_of_vertex_value, type_of_edge_weight>::setEdgeWeight(int from, int to, const type_of_edge_weight& new_weight) {//выставить вес
	auto iterator_vertex = table_.find(from);
	for(auto iterator_edge = iterator_vertex->second->out_edges.begin(); iterator_edge != iterator_vertex->second->out_edges.end(); ++iterator_edge)
		if(iterator_edge->to == to)
			iterator_edge->weight = new_weight;

	iterator_vertex = table_.find(to);
	for(auto iterator_edge = iterator_vertex->second->out_edges.begin(); iterator_edge != iterator_vertex->second->out_edges.end(); ++iterator_edge)
		if(iterator_edge->to == from)
			iterator_edge->weight = new_weight;
}
#endif