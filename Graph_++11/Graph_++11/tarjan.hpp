#include<list>
#include<map>

void connectLists(list<list<int> >& list_1,list<list<int> >& list_2) {
	for(auto iterator_list = list_2.begin(); iterator_list != list_2.end(); ++iterator_list)
		list_1.push_back(*iterator_list);
}

template<typename type_of_vertex_value, typename type_of_edge_weight>
void setColorToWhite(Graph<type_of_vertex_value, type_of_edge_weight>& current_graph) {
	auto vertices(current_graph.allVertices());
	
	for(auto iterator_vertices = vertices.begin(); iterator_vertices != vertices.end(); ++iterator_vertices)
		current_graph.setVertexColor(iterator_vertices->No_of_vertex, 0);
}


template<typename type_of_vertex_value, typename type_of_edge_weight>
list<list<int> >  tarjan(Graph<type_of_vertex_value, type_of_edge_weight> current_graph) {
	setColorToWhite(current_graph);

	list<list<int> > output_list;
	auto vertices(current_graph.allVertices());

	for(auto iterator_vertices = vertices.begin(); iterator_vertices != vertices.end(); ++iterator_vertices)
		if(current_graph.getVertexColor(iterator_vertices->No_of_vertex) == 0)
			connectLists(output_list,tarjanDFS(current_graph, iterator_vertices->No_of_vertex));

	return output_list;
}

class MapLowIndex {
private:
	map<int, int*> table_;
public:
	void addVertex(int No_of_vertex, int value) {
		int* temp_ptr = new int;
		*temp_ptr = value;
		table_.insert(pair<int, int*>(No_of_vertex,  temp_ptr));
	}
	void deleteVertex(int No_of_vertex) {
		auto iterator_table = table_.find(No_of_vertex);
		if(iterator_table != table_.end())
			delete (iterator_table->second);
	}
	void changeIndex(int No_of_vertex, int new_index) {
		auto iterator_table = table_.find(No_of_vertex);
		*(iterator_table->second) = new_index;
	}
	int returnIndex(int No_of_vertex) {
		auto iterator_table = table_.find(No_of_vertex);
		return *(iterator_table->second);
	}
	~MapLowIndex() {
		for(auto iterator_table = table_.begin(); iterator_table != table_.end(); ++iterator_table)
			delete (iterator_table->second);
	}
};

template<typename type_of_vertex_value, typename type_of_edge_weight>
list<list<int> > tarjanDFS(Graph<type_of_vertex_value, type_of_edge_weight>& current_graph, int No_of_vertex_begin) {
	list<list<int> > components;

	int current_vertex(No_of_vertex_begin);
	auto graph_iterator = current_graph.begin(current_vertex);
	graph_iterator.setVertexColor(1);

	int step = 0;
	list<int> stackDFS;
	list<int> stackALGO;
	map<int, int> index;
	MapLowIndex	low_index;

	stackDFS.push_back(current_vertex);
	stackALGO.push_back(current_vertex);
	index.insert(pair<int, int> (current_vertex, step));
	low_index.addVertex(current_vertex, step);
	
	while(1) {
		for(;!(graph_iterator == current_graph.end(current_vertex));++graph_iterator) {
			if(graph_iterator.getColorCurrentChild() == 1) {
				int low_index_child = low_index.returnIndex(graph_iterator.getCurrentChildNo());
				int current_index =  low_index.returnIndex(current_vertex);
				if(current_index > low_index_child) 
					low_index.changeIndex(current_vertex, low_index_child);
			}
			if(graph_iterator.getColorCurrentChild() == 0) {
				++step;
				current_vertex=(graph_iterator.getCurrentChildNo());
				stackDFS.push_back(current_vertex);
				stackALGO.push_back(current_vertex);
				index.insert(pair<int, int> (current_vertex, step));
				low_index.addVertex(current_vertex, step);
				graph_iterator.setColorCurrentChild(1);
				graph_iterator.goForward();
			}
		}
		if(low_index.returnIndex(current_vertex) == index.find(current_vertex)->second) {
			components.push_back(make_list(stackALGO, current_vertex));
		}
		if(current_vertex == No_of_vertex_begin) {
			break;
		}
		stackDFS.pop_back();
		graph_iterator = current_graph.begin(*(--stackDFS.end()));
		current_vertex = graph_iterator.getVertexNo();
	}
	return components;
}

list<int> make_list(list<int>& stackALGO, int No_of_vertex) {
	list<int> temp_list;
	int count = 1;
	auto iterator_list = --(stackALGO.end());
	for(;;--iterator_list) {
		if(*iterator_list == No_of_vertex)
			break;
		++count;
	}
	for(int i = 0; i < count; ++i) {
		temp_list.push_back(*iterator_list);
		iterator_list = stackALGO.erase(iterator_list);
	}
	return temp_list;
}