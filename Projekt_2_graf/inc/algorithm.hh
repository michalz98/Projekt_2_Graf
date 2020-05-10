#ifndef ALGORITHM_HH
#define ALGORITHM_HH

#include "graph.hh"

using std::cout;
using std::endl;
using std::cin;

const int maxint = std::numeric_limits<int>::max();


bool BellmanFordList(graph G,int n){
	int i, x;
	Edge *e;
	Vertex *v;
	bool change;

	for (i = 0; i< n-1 ; i++){
		change = false;
		for(x = 0; x < n ;x++){
			if (G.nl[x].first != NULL){
				for (e = G.nl[x].first; e != NULL ; e = e->nlnext){
					v = e->end;
					if (G.cost[x] != maxint && (G.cost[v->nr] > G.cost[x] + e->val)){
						change = true;
						G.cost[v->nr] = G.cost[x] + e->val;
						G.prev[v->nr] = x;
					}
				}
			}
		}
		if(!change){
			return true;
		}
	}

	for(x = 0; x < n;x++){
		for (e = G.nl[x].first; e != NULL; e = e->nlnext ){
			v = e->end;
			if (G.cost[v->nr] > G.cost[x] + e->val){
				return false;
			}
		}
	}

	return true;
}

bool BellmanFordMatrix(graph G,int n){
	int i, j, x;
	Edge *e;
	bool change;

	for (i = 0; i< n-1 ; i++){
		change = false;
		for(x = 0; x < n ;x++){
			for (j = 0; j < n; j++){
				if (G.matrix[x][j] != NULL){
					e = G.matrix[x][j];
					if (G.cost[x] != maxint && (G.cost[j] > G.cost[x] + e->val)){
						change = true;
						G.cost[j] = G.cost[x] + e->val;
						G.prev[j] = x;
					}
				}
			}
		}
		if(!change){
			return true;
		}
	}

	for(x = 0; x < n;x++){
		for (j = 0; j < n; j++){
			if (G.matrix[x][j] != NULL){
				e = G.matrix[x][j];
				if (G.cost[j] > G.cost[x] + e->val){
					return false;
				}
			}
		}
	}

	return true;
}


#endif
