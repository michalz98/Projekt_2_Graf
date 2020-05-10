#ifndef NMATRIX_HH
#define NMATRIX_HH

#include "structures.hh"


void PrepareMatrix(Edge ***matrix,int n){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			matrix[i][j] = NULL;
		}
	}
}

void AddEdgeM(int s, int e, Edge ***matrix, edge_list el){
	Edge *edge;
	for (edge = el.first; edge != NULL; edge = edge->next){
		if (edge->start->nr == s && edge->end->nr == e){
			matrix[s][e] = edge;
			matrix[e][s] = edge;
		}
	}
}

#endif
