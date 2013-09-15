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
	int from;//������
	int to;//����
	int color;//����(����� �����������)
	type_of_edge_weight weight;//��������
	Edge();//����������� �� ���������
	Edge(const Edge<type_of_edge_weight>& copy_edge);
	void operator =(const Edge<type_of_edge_weight>& to_equal_edge);
	template<typename type_of_edge_weight_1> friend ostream& operator <<(ostream& out, const Edge<type_of_edge_weight_1>& current_edge);
};

template<typename type_of_vertex_value, typename type_of_edge_weight>
struct Vertex {
public:
	int No_of_vertex;//����� �������
	int color;//����
	type_of_vertex_value value;//���������
	list<Edge<type_of_edge_weight> > out_edges;//������(� ����� ��������)
	list<Edge<type_of_edge_weight> > in_edges;//����������������� ����� � ��� ����, �������� ����������
	Vertex();//����������� �� ���������
	Vertex(int No);//�����������
	Vertex(const Vertex<type_of_vertex_value, type_of_edge_weight>& copy_vertex);//�����������
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
	void deleteEdgeSafe(int from, int to);//������ �����
	bool orientation_;//1 - ���������������, 0 - �����������������
	map<int, unique_ptr<Vertex<type_of_vertex_value, type_of_edge_weight> > > table_;//������� ���������� �� ������� - ������ �������, � ���� - �����, �����
public:
	Graph();//����������� �� ���������
	Graph(const bool& orientation);//����������� ��. = 1/����. = 0
	Graph(const Graph& copy_graph);//����������� �����������
	void operator =(const Graph& to_equal_graph);//������������
	bool operator ==(const Graph& compare_graph) const;//�������� �� ���������
	void addVertex(int No_of_new_vertex, const type_of_vertex_value& value);//�������� �� ��������� �� � ��� �������
	void addEdge(int from, int to, const type_of_edge_weight& weight);//������� �����
	void deleteVertex(int No_of_vertex);//�������� �� ��������� �� � ��� �������
	void deleteEdge(int from, int to);//������ �����
	void transpose();//���������������
	list<Edge<type_of_edge_weight> > getListOutEdges(int No_of_vertex) const;//������ ����� �� �������
	list<Vertex<type_of_vertex_value, type_of_edge_weight> > getListChildren(int No_of_vertex) const;//������ �������� ������
	list<Edge<type_of_edge_weight> > getListInEdges(int No_of_vertex) const;//������ ����� � �������
	list<Vertex<type_of_vertex_value, type_of_edge_weight> > getListParents(int No_of_vertex) const;//������ �������� ������, �� ������� ����� � ���
	list<Vertex<type_of_vertex_value, type_of_edge_weight> > allVertices() const;//������ ���� ������
	list<Edge<type_of_edge_weight> > allEdges() const;//������ ���� �����
	type_of_vertex_value getVertexValue(int No_of_vertex) const;//�������� ��, ��� ��������
	void setVertexValue(int No_of_vertex, const type_of_vertex_value& value);//�������� ��, ��� ��������
	int getVertexColor(int No_of_vertex) const;//�������� ����
	void setVertexColor(int No_of_vertex, int new_color);//�������� ����
	int getEdgeColor(int from, int to) const;//�������� ����
	void setEdgeColor(int from, int to, int new_color);//�������� ����
	type_of_edge_weight getEdgeWeight(int from, int to) const;//�������� ���
	void setEdgeWeight(int from, int to, const type_of_edge_weight& new_weight);//�������� ���
	template<typename type_of_vertex_value_1, typename type_of_edge_weight_1> friend ostream& operator <<(ostream& out, const Graph<type_of_vertex_value_1, type_of_edge_weight_1>& current_graph);//�����
	template<typename type_of_vertex_value_1, typename type_of_edge_weight_1> friend istream& operator >>(istream& in, Graph<type_of_vertex_value_1, type_of_edge_weight_1>& current_graph);//����

	friend class MyIterator;
	//template<typename type_of_vertex_value, typename type_of_edge_weight>
	class MyIterator {
	private:
		int from_;//����� �������, � ������� ��� ������
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
		type_of_vertex_value getVertexValue() {//�������� ��������
			return connected_graph->getVertexValue(from_);
		}
		int getVertexColor() {//�������� ����
			return connected_graph->getVertexColor(from_);
		}
		void setVertexValue(const type_of_vertex_value& new_value) {//�������� �������� ��
			connected_graph->setVertexValue(from_, new_value);
		}
		void setVertexColor(int new_color) {//�������� ����
			connected_graph->setVertexColor(from_, new_color);
		}
		int getVertexNo() {
			return from_;
		}
		type_of_vertex_value getValueCurrentChild() {//�������� ��������
			return connected_graph->getVertexValue(to_);
		}
		int getColorCurrentChild() {//�������� ����
			return connected_graph->getVertexColor(to_);
		}
		void setValueCurrentChild(const type_of_vertex_value& new_value) {//�������� �������� ��
			connected_graph->setVertexValue(to_, new_value);
		}
		void setColorCurrentChild(int new_color) {//�������� ����
			connected_graph->setVertexColor(to_, new_color);
		}
		int getCurrentChildNo() {
			return to_;
		}
		void operator =(const MyIterator& second) {//������������
			from_ = second.from_;
			to_ = second.to_;
			connected_graph = second.connected_graph;
		}
		Vertex<type_of_vertex_value, type_of_edge_weight> operator *() {//�������������, ���������� �������, ��� �� ������
			if(from_ == -1)
				return 0;
			
			return *(connected_graph->table_.find(from_)->second);
		}
		Vertex<type_of_vertex_value, type_of_edge_weight> operator -() {//�������������, ���������� �������-�������
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