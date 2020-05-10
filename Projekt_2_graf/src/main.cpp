#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <iomanip>
#include <limits>
#include <cstdlib>

#include "nlist.hh"
#include "nmatrix.hh"
#include "algorithm.hh"
#include "graph.hh"

using std::cout;
using std::endl;
using std::cin;
using std::ofstream;
using std::ifstream;
using std::string;


int random(int bot_range, int top_range)
{

	int range = top_range - bot_range;
	int rnd = bot_range + (std::rand()%range);
	return rnd;
}

int main(){

	int m, n, t;	//m - linczba E |....| n - liczba V |....| t - wybrany  V

	const int numrep = 100;
	char opt1,opt2;
	string filename,sfile;
	int i, j, s, e , w , *T, rep, d, opt;
	ofstream savefile;
	ifstream readfile;
	graph *G;

	cout << "\n__________PROGRAM START___________\n"<< endl;

	opt1 = 'a';
	while (opt1 != 'k'){
		opt = 0;
		opt2 = 'a';
		while(opt == 0){
			cout << "f - file" << endl;
			cout << "g - generate random" << endl;
			cout << "k - quit" << endl;
			cout << "option: ";
			cin >> opt1;
			if (opt1 == 'f' || opt1 == 'g' || opt1 == 'k'){
				opt = 1;
			} else {
				cout << "No option like: " << opt1 << endl;
			}
		}
	if(opt1 == 'f'){
		cout << "file: ";
		cin >> filename;
		cout << "save to file: ";
		cin >> sfile;
		//filename = "./data/graph.txt";
		//sfile = "./data/output.txt";
		ifstream readfile(filename);
		readfile >> m >> n >> t;
		G = new graph[1];

		G[0].MakeGraph(n);

		for (i = 0; i < n; i++){
			G[0].prev[i] = -1;
			G[0].cost[i] = maxint;
		}

		G[0].cost[t] = 0;
		PrepareMatrix(G[0].matrix, n);

		while(readfile >> s >> e >> w){
			G[0].AddToGraph(s,e,w);
		}
			//		MENU		//

		cout << "\nMENU:\n" << endl;
		cout << "m - menu" << endl;
		cout << "l - Bellman-Ford for list" << endl;
		cout << "x - Bellman-Ford for matrix" << endl;
		cout << "k - quit" << endl;
		while (opt2 != 'k'){
			cout << "\nChoose option (m - menu): " ;
			cin >> opt2;
			cout << endl;
			switch (opt2){
				case 'm':
					cout << "m - menu" << endl;
					cout << "l - Bellman-Ford for list" << endl;
					cout << "x - Bellman-Ford for matrix" << endl;
					cout << "k - quit" << endl;
					break;
				case 'l':
					if(BellmanFordList(G[0], n)){
						savefile.open(sfile);
						T = new int[n];
						j = 0;
						for(i = 0; i<n; i++){
							savefile << i <<": ";
							for(int x = i; x != -1; x = G[0].prev[x]){
								T[j++] = x;
							}
							while(j){
								savefile << T[--j] << " ";
							}
							if (G[0].cost[i] != maxint){
								savefile << "$ " << G[0].cost[i] <<endl;
							} else {
								savefile << "$ no connection" <<endl;
							}
						}
						savefile.close();
						delete []T;
					}
					break;
				case 'x':
					if(BellmanFordMatrix(G[0], n)){
						savefile.open(sfile);
						T = new int[n];
						j = 0;
						for(i = 0; i<n; i++){
							savefile << i <<": ";
							for(int x = i; x != -1; x = G[0].prev[x]){
								T[j++] = x;
							}
							while(j){
								savefile << T[--j] << " ";
							}
							if (G[0].cost[i] != maxint){
								savefile << "$ " << G[0].cost[i] <<endl;
							} else {
								savefile << "$ no connection" <<endl;
							}
						}
						savefile.close();
						delete []T;
					}
					break;
				case('k'):
					opt1 = opt2 = 'k';
					break;
			}
		}
	}

		if(opt1 == 'g'){
			sfile = "./data/output.txt";
			srand(time(NULL));

			cout << "chosen top - number of vertexes" << endl;
			cin >> t >> n;
			cout << endl;
			cout << "graph density: " << endl;
			cout << "1 - 25%" << endl;
			cout << "2 - 50%" << endl;
			cout << "3 - 75%" << endl;
			cout << "4 - 100%" << endl;
			cout << "   : ";
			cin >> d;
			if (d == 1){
				m = (n*(n-1)/2)*0.25;
			}
			if (d == 2){
				m = (n*(n-1)/2)*0.50;
			}
			if (d == 3){
				m = (n*(n-1)/2)*0.75;
			}
			if (d == 4){
				m = (n*(n-1)/2);
			}
			G = new graph[numrep];

			for(rep = 0; rep < numrep; rep++){

				G[rep].MakeGraph(n);

				for (i = 0; i < n; i++){
					G[rep].prev[i] = -1;
					G[rep].cost[i] = maxint;
				}

				G[rep].cost[t] = 0;
				PrepareMatrix(G[rep].matrix, n);

				if (d !=4){
					i = 0;
					//j = m;
					while(i < m){
						for(s=0;s<n;s++){
							e = random(0, n-1);
							if (s!=e && !(G[rep].SearchGraph(s,e))){
								w = random(1, 100);
								G[rep].AddToGraph(s,e,w);
								i++;
							}
						}
					}
				}else if(d == 4){
					for(i=0;i<n;i++){
						for(j=0;j<n;j++){
							w = random(1, 100);
							if(i != j){
								if (!(G[rep].SearchGraph(i,j))){
									G[rep].AddToGraph(i,j,w);
								}
							}
						}
					}
				}
			}

			cout << "\nMENU:\n" << endl;
			cout << "m - menu" << endl;
			cout << "l - Bellman-Ford for list" << endl;
			cout << "x - Bellman-Ford for matrix" << endl;
			cout << "b - back" << endl;
			cout << "k - quit" << endl;
			while (opt2 != 'k'){
				cout << "\nChoose option (m - menu): " ;
				cin >> opt2;
				cout << endl;
				switch (opt2){
				case 'm':
					cout << "m - menu" << endl;
					cout << "l - Bellman-Ford for list" << endl;
					cout << "x - Bellman-Ford for matrix" << endl;
					cout << "k - quit" << endl;
					break;
				case ('l'):
					sfile = "./data/list.txt";
					savefile.open(sfile);
					savefile.close();
					for(rep = 0; rep < numrep; rep++){
						auto start = std::chrono::high_resolution_clock::now();
						if(BellmanFordList(G[rep], n)){
							auto stop = std::chrono::high_resolution_clock::now();
							savefile.open(sfile,std::ios_base::app);
							savefile << std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count() << endl;
							savefile.close();
						}else {
							cout << "ERROR" << endl;
						}
					}
					break;
				case ('x'):
					sfile = "./data/matrix.txt";
					savefile.open(sfile);
					savefile.close();
					for(rep = 0; rep < numrep; rep++){
						auto start = std::chrono::high_resolution_clock::now();
						if(BellmanFordMatrix(G[rep], n)){
							auto stop = std::chrono::high_resolution_clock::now();
							savefile.open(sfile,std::ios_base::app);
							savefile << std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count() << endl;
							savefile.close();
						} else {
							cout << "ERROR" << endl;
						}
					}
					break;
				case ('b'):
					opt2 = 'k';
					break;
				case ('k'):
					opt1 = opt2 ='k';
					break;
				}
			}
		}
	}
	cout << "\n__________PROGRAM END___________\n"<< endl;

	return 0;
}
