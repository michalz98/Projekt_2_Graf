#ifndef GRAPH_HH
#define GRAPH_HH

#include "structures.hh"
#include "nlist.hh"
#include "nmatrix.hh"

struct graph{
	edge_list el;
	vertex_list vl;
	nlist *nl;
	Edge ***matrix;
	int *cost;
	int *prev;
	void AddToGraph(int s, int e, int v);
	bool SearchGraph(int s, int e);
	void MakeGraph(int n);
};

void graph::AddToGraph(int s, int e,int w){
	if (!(vl.Search(s))){
		vl.AddVertex(s);
	}

	if (!(vl.Search(e))){
		vl.AddVertex(e);
	}

	if (!(el.Search(s,e))){
		el.AddEdge(s,e,w,vl);
	}

	if (!(el.Search(e,s))){
		el.AddEdge(e,s,w,vl);
	}

	if (!(nl[s].Search(s,e))){
		nl[s].AddEdge(s,e,el);
	}
	if (!(nl[e].Search(e,s))){
		nl[e].AddEdge(e,s,el);
	}
	AddEdgeM(s,e,matrix,el);
}

bool graph::SearchGraph(int s, int e){
	if (el.Search(s,e) || el.Search(e,s)){
		return true;
	}
	return false;

}

void graph::MakeGraph(int n){

	nl = new nlist[n];
	cost = new int[n];
	prev = new int[n];
	matrix = new Edge**[n];
	for (int i = 0; i < n; i++){
		matrix[i] = new Edge*[n];
	}
}

#endif
