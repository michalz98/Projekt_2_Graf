#ifndef STRUCTURES_HH
#define STRUCTURES_HH

using std::cout;
using std::endl;



/*!
 * obiekt typu wierzcholek
 * 	nr - numer wierzcholka
 * 	ref_lvertex - referencja do listy wierzcholkow
 * 	next - wskaznik na nastepny wierzcholek w liscie
 */
struct Vertex{
	int nr;
	Vertex *next;
	int key;
};


/*!
 * obiekt typu krawedz
 * 	val - wartosc krawedzi
 * 	start - wierzcholek startowy
 * 	end - wierzcholek koncowy
 * 	next - wskaznik na nastepna krawed
 * 	ref_elist - referencja do listy krawedzi
 * 	ref_nlist_start - referencja do listy sasiedztwa dla wierzcholka poczatkowego
 * 	ref_nlist_start - referencja do listy sasiedztwa dla wierzcholka koncowego
 */
struct Edge{
	int val;
	Vertex *start;
	Vertex *end;
	Edge *next;
	Edge *nlnext;
};


struct vertex_list{
	Vertex *first;
	Vertex *last;
	void AddVertex(int nr);
	void RemoveVertex(int nr);
	bool Search(int nr);
	vertex_list();
};

void vertex_list::AddVertex(int nr){
	Vertex *tmp = new Vertex;
	tmp->nr =nr;
	tmp->next = NULL;
	if (first == NULL){
		first = tmp;
		last = tmp;
	} else{
		last->next = tmp;
		last = tmp;
	}
}

void vertex_list::RemoveVertex(int nr){
	Vertex *tmp_prev;
	Vertex *tmp;
	tmp = first;
	if (first->nr == nr){
		first = tmp->next;
	} else {
		while(tmp->nr != nr){
			tmp_prev = tmp;
			tmp = tmp->next;
		}
		tmp_prev->next = tmp->next;
	}
}

bool vertex_list::Search(int nr){
	Vertex *tmp;
	for(tmp = first; tmp != NULL; tmp = tmp->next){
		if (tmp->nr == nr){
			return true;
		}
	}
	return false;
}

vertex_list::vertex_list(){
	first = NULL;
	last = NULL;
}



struct edge_list{
	Edge *first;
	Edge *last;
	void AddEdge(int s, int e, int v, vertex_list vl);
	void RemoveEdge(int s, int e);
	bool Search(int s, int e);
	edge_list();
};

void edge_list::AddEdge(int s, int e,int v, vertex_list vl){
	Edge *edge = new Edge;
	Vertex *tmp = vl.first;
	while(tmp->nr != s){
		tmp = tmp->next;
	}
	edge->start = tmp;
	tmp = vl.first;
	while(tmp->nr != e){
		tmp = tmp->next;
	}
	edge->end = tmp;
	edge->val =v;
	edge->next = NULL;
	edge->nlnext = NULL;
	if (first == NULL){
		first = edge;
		last = edge;
	} else{
		last->next = edge;
		last = edge;
	}
}

void edge_list::RemoveEdge(int s, int e){
	Edge *tmp_prev;
	Edge *tmp;
	tmp = first;
	if (first->start->nr == s && first->end->nr == e){
		first = tmp->next;
	} else {
		while(tmp->start->nr != s && tmp->end->nr != e){
			tmp_prev = tmp;
			tmp = tmp->next;
		}
		tmp_prev->next = tmp->next;
	}
}

bool edge_list::Search(int s, int e){
	Edge *tmp;
	for (tmp = first; tmp != NULL; tmp = tmp->next){
		if (tmp->start->nr == s && tmp->end->nr == e){
			return true;
		}
	}
	return false;
}

edge_list::edge_list(){
	first = NULL;
	last = NULL;
}


#endif
