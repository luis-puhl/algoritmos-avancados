#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;
#define MAXCANDIDATES 64
#define ECHO printf("#\n");

int isDiagonal(int src, int dest, int boardSize){
	int ax, ay, bx, by;
	
	if (src == dest){
		return 1;
	}
	
	ax = src / boardSize; // linha
	ay = src % boardSize; // coluna
	
	bx = dest / boardSize; // linha
	by = dest % boardSize; // coluna
	
	if (ax-ay == bx-by || ax+ay == bx+by){
		return 1;
	}
	return 0;
}

long long int sol = 0;
void process_solution(vector<int> a){
	sol++;
	printf("\tresult #%lld", sol);
	printf("\tBISPOS { ");
	for (vector<int>::iterator i = a.begin(); i < a.end(); ++i){
		printf("%d, ", *i);
	}
	printf("}\n");
}

vector<int> *filter(vector<int> d, int bisp, int boardsize){
	vector<int> *nd;
	nd = new vector<int>();
	
	for (vector<int>::iterator it = d.begin(); it < d.end(); ++it){
		if ( !isDiagonal(*it, bisp, boardsize) ){
			nd->push_back(*it);
		}
	}
	
	return nd;
}

void backtrack(vector<int> a, vector<int> d, int k_bis, int n_tab){
	vector<int> *nd;
	
	printf("len %lu, poss %lu\n", a.size(), d.size());
	
	if ( ((int)a.size()) == k_bis ){
		process_solution(a);
	} else {
		printf("\t\tbacktrack_prevCand { ");
		for (vector<int>::iterator i = d.begin(); i < d.end(); i++){
			printf("%d, ", *i);
		}
		printf("}\n");
		printf("\t\tbacktrack_prevBisp { ");
		for (vector<int>::iterator i = a.begin(); i < a.end(); i++){
			printf("%d, ", *i);
		}
		printf("}\n");
		
		for (vector<int>::iterator i = d.begin(); i < d.end(); i++){
			printf("\tk= %lud, i= %d\n", a.size(), *i);
			
			a.push_back(*i);
			nd = filter(d, *i, n_tab);
			backtrack(a, *nd, k_bis, n_tab);
			delete nd;
			a.pop_back();
		}
	}
}


void bishops(int k_bis, int n_tab){
	vector<int> a, d;
	int i;
	sol = 0;
	
	int numOpcoes = n_tab * n_tab;
	for (i = 0; i < numOpcoes; i++){
		//~ printf("alocando para %d\n", i);
		d.push_back(i);
	}
	
	backtrack(a, d, k_bis, n_tab);
	printf("F(k_bis, n_tab) (%d, %d) = %lld\n", k_bis, n_tab, sol);
}

int main(int argc, char **argv){
	bishops(2,2);
	//~ bishops(3,3);
	//~ bishops(3,4);
	//~ bishops(4,4);
	return 0;
}
