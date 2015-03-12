#include <stdio.h>
#include <iostream>
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
	#ifdef DEBUG
	printf("result #%ld", sol);
	printf("\tBISPOS { ");
	for (vector<int>::iterator i = a.begin(); i < a.end(); ++i){
		printf("%d, ", *i);
	}
	printf("}\n");
	#endif
}

vector<int> *filter(vector<int> *d, int bisp, int boardsize){
	vector<int> *nd;
	nd = new vector<int>();
	
	#ifdef DEBUG
	printf("\t\tprevCand { ");
	if (d != NULL){
		for (vector<int>::iterator i = d->begin(); i < d->end(); i++){
			printf("%d, ", *i);
		}
	}
	printf("}\n");
	#endif
	
	if (d == NULL){
		int numOpcoes = boardsize * boardsize;
		d = new vector<int>();
		for (int i = 0; i < numOpcoes; i++){
			d->push_back(i);
		}
	}
	
	for (vector<int>::iterator it = d->begin(); it < d->end(); ++it){
		// se o valor for negativo ou o bispo alocado anteriormente é maior que a casa analisada
		if (*it < 0 || bisp >= *it){
			continue;
		}
		if (bisp < 0){
			nd->push_back(*it);
			continue;
		}
		if ( !isDiagonal(*it, bisp, boardsize) ){
			nd->push_back(*it);
		}
	}
	
	#ifdef DEBUG
	printf("\t\tCand { ");
	for (vector<int>::iterator i = nd->begin(); i < nd->end(); i++){
		printf("%d, ", *i);
	}
	printf("}\n");
	#endif
	
	return nd;
}


unsigned long long int nodes = 0;
void backtrack(vector<int> a, vector<int> *d, int k_bis, int n_tab, int k){
	vector<int> *nd;
	nodes++;
	#ifdef DEBUG
	printf("\n\tlen %lu, poss %lu\n", a.size(), d!=NULL?d->size():0);
	
	printf("\tbacktrack_prevBisp { ");
	for (vector<int>::iterator i = a.begin(); i < a.end(); i++){
		printf("%d, ", *i);
	}
	printf("}\n");
	#endif
	
	if ( ((int)a.size()) == k_bis ){
		process_solution(a);
	} else {
		nd = filter(d, k, n_tab);
		// se as possiveis alocacoes sao menores que as casas para uma solucao
		if ( nd->size() < (k_bis - a.size()) ){
			return;
		}
		for (vector<int>::iterator i = nd->begin(); i < nd->end(); i++){
			#ifdef DEBUG
			printf("\tk= %lud, BISPO= %d\n", a.size(), *i);
			#endif
			// se a casa atual for mais alta do que as casas necessarias para achar uma solucao
			if ( *i > (n_tab * n_tab) - (k_bis - (int)a.size()) ){
				return;
			}
			a.push_back(*i);
			backtrack(a, nd, k_bis, n_tab, *i);
			a.pop_back();
		}
		delete nd;
	}
}

long long int bishopsDyna[65][9];
long long int bishops(int k_bis, int n_tab){
	vector<int> a, *d;
	sol = 0;
	nodes = 0;
	d = NULL;
	if (k_bis <= n_tab*n_tab){
		if (bishopsDyna[k_bis][n_tab] > 0){
			sol = bishopsDyna[k_bis][n_tab];
		} else /* devia ter uma terceira opçao aqui, mas esqueci qual era */{
			backtrack(a, d, k_bis, n_tab, -1);
		}
	}
	#ifdef SHOW_RESULT
	printf("F(k_bis, n_tab) (%d, %d) = %lld with %llu nodes\n", k_bis, n_tab, sol, nodes);
	#endif
	bishopsDyna[k_bis][n_tab] = sol;
	return sol;
}

void init(){
	for (int i = 0; i <= 64; i++){
		for (int j = 0; j <= 8; j++){
			bishopsDyna[i][j] = 0;
		}
	}
}

int main(int argc, char **argv){
	init();
	
	bishops(8, 8);
	
	//~ int k, n;
	//~ while(cin >> n >> k){
		//~ if (n==0 && k==0){
			//~ break;
		//~ }
		//~ printf("%lld\n", bishops(k, n) );
		//~ 
	//~ }
	
	//~ printf("long long int bishopsDyna[8][8] = {");
	//~ for (int i = 0; i <= 8; i++){
		//~ for (int j = 0; j <= 8; j++){
			//~ long long int k = bishops(i, j);
			//~ printf("%lld", k);
			//~ if ( i!= 8 && j != 8){
				//~ printf(", ");
			//~ }
		//~ }
	//~ }
	//~ printf("};\n");
	//~ 
	//~ for (int i = 0; i <= 8; i++){
		//~ for (int j = 0; j <= 8; j++){
			//~ long long int k = bishopsDyna[i][j];
			//~ printf("%lld\n", k);
		//~ }
	//~ }
	
	//~ bishops(2,2);
	//~ bishops(3,3);
	//~ bishops(3,4);
	//~ bishops(4,4);
	//~ bishops(5,5);
	//~ bishops(6,6);
	//~ bishops(7,7);
	//~ bishops(9,8);
	return 0;
}
