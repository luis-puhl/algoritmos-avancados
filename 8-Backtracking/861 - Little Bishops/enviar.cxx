#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <cmath>
using namespace std;
typedef unsigned int tpos;
typedef int ttab;

int isDiagonal(ttab src, ttab dest, ttab boardSize){
	ttab ax, ay, bx, by;
	
	if (src == dest){
		return 1;
	}
	
	ax = src / boardSize;
	ay = src % boardSize;
	
	bx = dest / boardSize;
	by = dest % boardSize;
	
	if (ax-ay == bx-by || ax+ay == bx+by){
		return 1;
	}
	return 0;
}

tpos sol = 0;
void process_solution(vector<ttab> a){
	sol++;
}

vector<ttab> *filter(vector<ttab> *d, ttab bisp, ttab boardsize){
	vector<ttab> *nd;
	nd = new vector<ttab>();
	
	if (d == NULL){
		ttab numOpcoes = boardsize * boardsize;
		d = new vector<ttab>();
		for (int i = 0; i < numOpcoes; i++){
			d->push_back(i);
		}
	}
	
	for (vector<ttab>::iterator it = d->begin(); it < d->end(); ++it){
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
	
	return nd;
}

unsigned long int nodes = 0;
void backtrack(vector<ttab> a, vector<ttab> *d, ttab k_bis, ttab n_tab, ttab k){
	vector<ttab> *nd;
	nodes++;
	
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
		
		if (
			nd->size()
			>= (k_bis - a.size())
		){
			for (vector<ttab>::iterator i = nd->begin(); i < nd->end(); i++){
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

unsigned int bishopsDyna[65][9] = 
 {1, 1, 1, 1, 1, 1, 1, 1, 1,
0, 1, 4, 9, 16, 25, 36, 49, 64,
0, 0, 4, 26, 92, 240, 520, 994, 1736,
0, 0, 0, 26, 232, 1124, 3896, 10894, 26192,
0, 0, 0, 8, 260, 2728, 16428, 70792, 242856,
0, 0, 0, 0, 112, 3368, 39680, 282248, 1444928,
0, 0, 0, 0, 16, 1960, 53744, 692320, 5599888,
0, 0, 0, 0, 0, 440, 38368, 1022320, 14082528,
0, 0, 0, 0, 0, 32, 12944, 867328, 22522960,
0, 0, 0, 0, 0, 0, 1600, 389312, 22057472,
0, 0, 0, 0, 0, 0, 64, 81184, 12448832,
0, 0, 0, 0, 0, 0, 0, 5792, 3672448,
0, 0, 0, 0, 0, 0, 0, 128, 489536,
0, 0, 0, 0, 0, 0, 0, 0, 20224,
0, 0, 0, 0, 0, 0, 0, 0, 256};

tpos bishops(int k_bis, int n_tab){
	vector<ttab> a, *d;
	sol = 0;
	nodes = 0;
	d = NULL;
	if (k_bis <= n_tab*n_tab){
		if (bishopsDyna[k_bis][n_tab] > 0){
			sol = bishopsDyna[k_bis][n_tab];
		} else if(n_tab > 1 && k_bis > (n_tab-1)*2){
			sol = 0;
		} else if (k_bis == 0){
			sol = 1;
		} else if (k_bis == 1){
			sol = n_tab * n_tab;
		} else if (n_tab == 1){
			sol = 1;
		} else {
			backtrack(a, d, k_bis, n_tab, -1);
		}
	}
	bishopsDyna[k_bis][n_tab] = sol;
	return sol;
}

int main(int argc, char **argv){
	
	int k, n;
	while(cin >> n >> k){
		if (n==0 && k==0){
			break;
		}
		printf("%u\n", bishops(k, n) );
	}
	
	return 0;
}
