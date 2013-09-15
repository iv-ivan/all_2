#ifndef _GRAPH
#define _GRAPH

#include<iostream>
#include<map>
#include<list>
#include<memory>
using namespace std;

template<typename type_of_edge_weight>
struct Edge {
public:
	int from;//откуда
	int to;//куда
	int color;//цвет(вдруг понадобится)
	type_of_edge_weight weight;//значение
	Edge();//конструктор по умолчанию
	Edge(const Edge<type_of_edge_weight>& copy_edge);
	void operator =(const Edge<type_of_edge_weight>& to_equal_edge);
	template<typename type_of_edge_weight_1> friend ostream& operator <<(ostream& out, const Edge<type_of_edge_weight_1>& current_edge);
};

template<typename type_of_vertex_value, typename type_of_edge_weight>
struct Vertex {
public:
	int No_of_vertex;//номер вершины
	int color;//цвет
	type_of_vertex_value value;//знасчение
	list<Edge<type_of_edge_weight> > out_edges;//соседи(и ребра косвенно)
	list<Edge<type_of_edge_weight> > in_edges;//транспонированные ребра в эту точк, фиктивно настоящиеу
	Vertex();//конструктор по умолчанию
	Vertex(int No);//конструктор
	Vertex(const Vertex<type_of_vertex_value, type_of_edge_weight>& copy_vertex);//конструктор
	void operator =(const Vertex<type_of_vertex_value, type_of_edge_weight>& to_equal_vertex);
	bool operator >(const Vertex& compare_vertex) const;
	bool operator <(const Vertex& compare_vertex) const;
	bool operator ==(const Vertex& compare_vertex) const;
	bool operator >=(const Vertex& compare_vertex) const;
	bool operator <=(const Vertex& compare_vertex) const;
	template<typename type_of_vertex_value_1, typename type_of_edge_weight_1> friend ostream& operator <<(ostream& out, const Vertex<type_of_vertex_value_1, type_of_edge_weight_1>& current_vertex);
};

template<typename type_of_vertex_value, typename type_of_edge_weight>
class Graph {
private:
	void addEdgeSafe(int from, int to, const type_of_edge_weight& weight);
	void deleteEdgeSafe(int from, int to);//удалит ребро
	bool orientation_;//1 - ориентированный, 0 - неориентированный
	map<int, unique_ptr<Vertex<type_of_vertex_value, type_of_edge_weight> > > table_;//таблица указателей на вершины - индекс вектора, в паре - сосед, ребро
public:
	Graph();//конструктор по умолчанию
	Graph(const bool& orientation);//конструктор ор. = 1/неор. = 0
	Graph(const Graph& copy_graph);//конструктор копирования
	void operator =(const Graph& to_equal_graph);//присваивание
	bool operator ==(const Graph& compare_graph) const;//проверка на равенство
	void addVertex(int No_of_new_vertex, const type_of_vertex_value& value);//добавить не связанную ни с кем вершину
	void addEdge(int from, int to, const type_of_edge_weight& weight);//добавит ребро
	void deleteVertex(int No_of_vertex);//добавить не связанную ни с кем вершину
	void deleteEdge(int from, int to);//удалит ребро
	void transpose();//транспонировать
	list<Edge<type_of_edge_weight> > getListOutEdges(int No_of_vertex) const;//список ребер из вершины
	list<Vertex<type_of_vertex_value, type_of_edge_weight> > getListChildren(int No_of_vertex) const;//список соседних вершин
	list<Edge<type_of_edge_weight> > getListInEdges(int No_of_vertex) const;//список ребер в вершину
	list<Vertex<type_of_vertex_value, type_of_edge_weight> > getListParents(int No_of_vertex) const;//список соседних вершин, из которых ведет к нам
	list<Vertex<type_of_vertex_value, type_of_edge_weight> > allVertices() const;//список всех вершин
	list<Edge<type_of_edge_weight> > allEdges() const;//список всех ребер
	type_of_vertex_value getVertexValue(int No_of_vertex) const;//получить то, что хранится
	void setVertexValue(int No_of_vertex, const type_of_vertex_value& value);//изменить то, что хранится
	int getVertexColor(int No_of_vertex) const;//получить цвет
	void setVertexColor(int No_of_vertex, int new_color);//изменить цвет
	int getEdgeColor(int from, int to) const;//получить цвет
	void setEdgeColor(int from, int to, int new_color);//изменить цвет
	type_of_edge_weight getEdgeWeight(int from, int to) const;//получить вес
	void setEdgeWeight(int from, int to, const type_of_edge_weight& new_weight);//получить вес
	template<typename type_of_vertex_value_1, typename type_of_edge_weight_1> friend ostream& operator <<(ostream& out, const Graph<type_of_vertex_value_1, type_of_edge_weight_1>& current_graph);//вывод
	template<typename type_of_vertex_value_1, typename type_of_edge_weight_1> friend istream& operator >>(istream& in, Graph<type_of_vertex_value_1, type_of_edge_weight_1>& current_graph);//ввод

	friend class MyIterator;
	//template<typename type_of_vertex_value, typename type_of_edge_weight>
	class MyIterator {
	private:
		int from_;//номер вершины, в которой мцы сейчас
		int to_;
		Graph<type_of_vertex_value, type_of_edge_weight>* connected_graph;
	public:
		friend class Graph<type_of_vertex_value, type_of_edge_weight>;
		MyIterator() {
			from_ = -1;
			to_ = -1;
			connected_graph = NULL;
		}
		MyIterator operator ++() {
			if(to_ == -1 || from_ == -1)
				return *this;

			/*set<Vertex<type_of_vertex_value, type_of_edge_weight>* >::iterator*/auto iterator_current_vertex = connected_graph->table_.find(from_);
			
			/*list<Edge<type_of_edge_weight> >::const_iterator*/auto iterator_out_edge = iterator_current_vertex->second->out_edges.begin();
			while(iterator_out_edge->to != to_)
				++iterator_out_edge;

			++iterator_out_edge;

			if(iterator_out_edge == iterator_current_vertex->second->out_edges.end())
				to_ = -1;
			else
				to_ = iterator_out_edge->to;

			return *this;
		}
		void goForward() {
			if(to_ != -1 && from_ != -1)
				*this = connected_graph->begin(to_);
		}
		type_of_vertex_value getVertexValue() {//получить значение
			return connected_graph->getVertexValue(from_);
		}
		int getVertexColor() {//получить цвет
			return connected_graph->getVertexColor(from_);
		}
		void setVertexValue(const type_of_vertex_value& new_value) {//изменить значение на
			connected_graph->setVertexValue(from_, new_value);
		}
		void setVertexColor(int new_color) {//изменить цвет
			connected_graph->setVertexColor(from_, new_color);
		}
		int getVertexNo() {
			return from_;
		}
		type_of_vertex_value getValueCurrentChild() {//получить значение
			return connected_graph->getVertexValue(to_);
		}
		int getColorCurrentChild() {//получить цвет
			return connected_graph->getVertexColor(to_);
		}
		void setValueCurrentChild(const type_of_vertex_value& new_value) {//изменить значение на
			connected_graph->setVertexValue(to_, new_value);
		}
		void setColorCurrentChild(int new_color) {//изменить цвет
			connected_graph->setVertexColor(to_, new_color);
		}
		int getCurrentChildNo() {
			return to_;
		}
		void operator =(const MyIterator& second) {//присваивание
			from_ = second.from_;
			to_ = second.to_;
			connected_graph = second.connected_graph;
		}
		Vertex<type_of_vertex_value, type_of_edge_weight> operator *() {//разыменование, возвращает вершину, где мы сейчас
			if(from_ == -1)
				return 0;
			
			return *(connected_graph->table_.find(from_)->second);
		}
		Vertex<type_of_vertex_value, type_of_edge_weight> operator -() {//разыменование, возвращает вершину-потомка
			if(to_ == -1)
				return 0;
			
			return *(connected_graph->table_.find(to_)->second);
		}
		bool operator ==(const MyIterator& second) {
			return (from_ == second.from_) && (to_ == second.to_) && (connected_graph == second.connected_graph);
		}
	};
	MyIterator begin(int from) {
		MyIterator new_iterator;
		new_iterator.connected_graph = this;
		new_iterator.from_ = from;
		/*set<Vertex<type_of_vertex_value, type_of_edge_weight> >::iterator*/auto iterator_vertex_from = table_.find(from);
		/*list<Edge<type_of_edge_weight> >::const_iterator*/auto iterator_edge = iterator_vertex_from->second->out_edges.begin();
		if(iterator_vertex_from->second->out_edges.empty())
			new_iterator.to_ = -1;
		else
			new_iterator.to_ = iterator_edge->to;
		return new_iterator;
	}

	MyIterator end(int from) {
		MyIterator new_iterator;
		new_iterator.connected_graph = this;
		new_iterator.to_ = -1;
		new_iterator.from_ = from;
		return new_iterator;
	}
};

#include"graph.hpp"
#endif