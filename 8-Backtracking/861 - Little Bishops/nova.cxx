#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <cmath>
using namespace std;
#define MAXCANDIDATES 64
#define ECHO printf("#\n");
typedef unsigned int tpos;
typedef int ttab;

//~ #define DEBUG
//~ #define SHOW_RESULT

int isDiagonal(ttab src, ttab dest, ttab boardSize){
	ttab ax, ay, bx, by;
	
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

tpos sol = 0;
void process_solution(vector<ttab> a){
	sol++;
	#ifdef DEBUG
	printf("result #%u", sol);
	printf("\tBISPOS { ");
	for (vector<int>::iterator i = a.begin(); i < a.end(); ++i){
		printf("%d, ", *i);
	}
	printf("}\n");
	#endif
}

vector<ttab> *filter(vector<ttab> *d, ttab bisp, ttab boardsize){
	vector<ttab> *nd;
	nd = new vector<ttab>();
	
	#ifdef DEBUG
	printf("\t\tprevCand { ");
	if (d != NULL){
		for (vector<ttab>::iterator i = d->begin(); i < d->end(); i++){
			printf("%d, ", *i);
		}
	}
	printf("}\n");
	#endif
	
	if (d == NULL){
		ttab numOpcoes = boardsize * boardsize;
		d = new vector<ttab>();
		for (int i = 0; i < numOpcoes; i++){
			d->push_back(i);
		}
	}
	
	for (vector<ttab>::iterator it = d->begin(); it < d->end(); ++it){
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
	for (vector<ttab>::iterator i = nd->begin(); i < nd->end(); i++){
		printf("%d, ", *i);
	}
	printf("}\n");
	#endif
	
	return nd;
}

unsigned long int nodes = 0;
void backtrack(vector<ttab> a, vector<ttab> *d, ttab k_bis, ttab n_tab, ttab k){
	vector<ttab> *nd;
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
	} else if ( ((int)a.size()) == k_bis - 1 ){
		nd = filter(d, k, n_tab);
		for (vector<ttab>::iterator i = nd->begin(); i < nd->end(); i++){
			a.push_back(*i);
			process_solution(a);
			a.pop_back();
		}
		delete nd;
	} else {
		nd = filter(d, k, n_tab);
		
		// se as possiveis alocacoes sao menores que as casas para uma solucao
		if (
			nd->size() // possibilidades de alocar
			>= (k_bis - a.size()) // quantos bispos falta
		){
			for (vector<ttab>::iterator i = nd->begin(); i < nd->end(); i++){
				#ifdef DEBUG
				printf("\tk= %lud, BISPO= %d\n", a.size(), *i);
				#endif
				// se a casa atual for mais alta do que as casas necessarias para achar uma solucao
				if ( *i > (n_tab * n_tab) - (k_bis - (int)a.size()) ){
					break;
				}
				a.push_back(*i);
				backtrack(a, nd, k_bis, n_tab, *i);
				a.pop_back();
			}
		}
		delete nd;
	}
}

tpos bishopsDyna[15][9];
tpos bishops(int k_bis, int n_tab){
	if (k_bis >= 15){
		return 0;
	}
	
	vector<ttab> a, *d;
	sol = 0;
	nodes = 0;
	d = NULL;
	
	if (k_bis <= n_tab*n_tab){
		if (bishopsDyna[k_bis][n_tab] > 0){
			// prog dinamica sempre ajuda =D
			sol = bishopsDyna[k_bis][n_tab];
		} else if(n_tab > 1 && k_bis > (n_tab-1)*2){
			// limite de alocação, a solução é zero para este caso 
			sol = 0;
		} else if (k_bis == 0){
			sol = 1;
		} else if (k_bis == 1){
			sol = n_tab * n_tab;
		} else if (n_tab == 1){
			sol = 1;
		//~ } else if (n_tab != 1 && k_bis == (2 * n_tab) -1 ){
			//~ sol = ((unsigned long long int) 2) << n_tab ;
		} else {
			backtrack(a, d, k_bis, n_tab, -1);
		}
	}
	#ifdef SHOW_RESULT
	printf("F(k_bis, n_tab) (%d, %d) = %u \nwith %lu nodes\n", k_bis, n_tab, sol, nodes);
	#endif
	bishopsDyna[k_bis][n_tab] = sol;
	return sol;
}

void init(){
	for (int i = 0; i <= 14; i++){
		for (int j = 0; j <= 8; j++){
			bishopsDyna[i][j] = 0;
		}
	}
}

int main(int argc, char **argv){
	init();
	
	//~ bishops(8, 8);
	
	//~ int k, n;
	//~ while(cin >> n >> k){
		//~ if (n==0 && k==0){
			//~ break;
		//~ }
		//~ printf("%lld\n", bishops(k, n) );
		//~ 
	//~ }
	
	for (int i = 0; i <= 14; i++){
		for (int j = 0; j <= 8; j++){
			bishops(i, j);
		}
	}
	printf("\n");
	
	printf("unsigned int bishopsDyna[15][9] = {");
	for (int i = 0; i <= 14; i++){
		for (int j = 0; j <= 8; j++){
			tpos k = bishopsDyna[i][j];
			printf("%u", k);
			if ( i != 14 && j != 8){
				printf(", ");
			}
		}
		printf("\n");
	}
	printf("};\n");
	
	return 0;
}
