#include"graph.h"
#include"tarjan.hpp"
#include<fstream>
#include<iostream>
#include"Prim.hpp"
using namespace std;

int main() 
{
	ifstream in("input.txt");
	Graph<int,int> my_graph(0);
	in>>my_graph;
	//auto a = tarjan(my_graph);
	//square(2);
	//my_graph.setEdgeWeight(1,2,88);
	//int a = my_graph.getEdgeWeight(1,2);
	//Graph<int,int> my_graph_2(my_graph);
	//my_graph_2.deleteEdge(1,2);
	//cout << a;//my_graph;*/
	cout << Prim(my_graph);
	return 0;
}