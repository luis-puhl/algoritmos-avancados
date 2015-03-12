#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

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

long int sol = 0;
void process_solution(vector<int> a){
	sol++;
}

vector<int> *filter(vector<int> *d, int bisp, int boardsize){
	vector<int> *nd;
	nd = new vector<int>();
	
	if (d == NULL){
		int numOpcoes = boardsize * boardsize;
		d = new vector<int>();
		for (int i = 0; i < numOpcoes; i++){
			d->push_back(i);
		}
	}
	
	for (vector<int>::iterator it = d->begin(); it < d->end(); ++it){
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

void backtrack(vector<int> a, vector<int> *d, int k_bis, int n_tab, int k){
	vector<int> *nd;
	if ( ((int)a.size()) == k_bis ){
		process_solution(a);
	} else {
		//~ d = filter(d, k, n_tab);
		nd = filter(d, k, n_tab);
		if ( d->size() < (k_bis - a.size()) ){
			return;
		}
		for (vector<int>::iterator i = nd->begin(); i < nd->end(); i++){
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

long long int bishopsDyna[9][9];
long long int bishops(int k_bis, int n_tab){
	vector<int> a, *d;
	sol = 0;
	d = NULL;
	if (k_bis <= n_tab && n_tab <= 8){
		if (bishopsDyna[k_bis][n_tab] > 0){
			sol = bishopsDyna[k_bis][n_tab];
		} else {
			backtrack(a, d, k_bis, n_tab, -1);
		}
	}
	printf("F(k_bis, n_tab) (%d, %d) = %ld\n", k_bis, n_tab, sol);
	return sol;
}

int main(int argc, char **argv){
	int k, n;
	while (scanf("%d %d", &k, &n)){
		if (n==0 && k==0){
			break;
		}
		printf("%lld\n", bishops(k, n) );
	}
	return 0;
}
