#ifndef NLIST_HH
#define NLIST_HH

#include "structures.hh"

using std::cout;
using std::endl;

struct nlist{
	Edge *first;
	Edge *last;
	void AddEdge(int s, int e, edge_list el);
	bool Search(int s, int e);
	void ShowV();
	nlist();
};

void nlist::ShowV(){
	Edge *tmp;

	cout << "first: " << first->start->nr << endl;
	for(tmp = first; tmp != NULL; tmp = tmp->nlnext){
		cout << tmp->start->nr;
		cout << tmp->end->nr << endl;;
		cout << "value:" << tmp->val << endl;
	}
	cout << "koniec listy" << endl;
}

void nlist::AddEdge(int s, int e, edge_list el){
	Edge *edge;
	for (Edge *tmpe = el.first; tmpe != NULL; tmpe = tmpe->next){
		if (tmpe->start->nr == s && tmpe->end->nr == e){
			edge = tmpe;
		}
	}
	if (first == NULL){
		first = edge;
		last = edge;
	} else{
		last->nlnext = edge;
		last = edge;
	}
}

bool nlist::Search(int s, int e){
	Edge *tmp;
	for(tmp = first; tmp !=NULL ; tmp = tmp->nlnext){
		if (tmp->start->nr == s && tmp->end->nr == e){
			return true;
		}
	}
	return false;
}

nlist::nlist(){
	first = NULL;
	last = NULL;
}


#endif
