#include <stdio.h>
#include <cmath>
using namespace std;
#define MAXCANDIDATES 64
//~ #define DEBUG
int finished = 0;		/* found all solutions yet? */
typedef struct{
	int k_bis;
	int n_tab;
} data;

void construct_candidates(int[], int, data, int[], int*);
int is_a_solution(int[], int, data);
void process_solution(int[], int, data);

void backtrack(int a[], int k, data input){
	int c[MAXCANDIDATES];	/* candidates for next position */
	int ncandidates;		/* next position candidate count */
	int i;					/* counter */
	
	if (is_a_solution(a, k, input))
		process_solution(a, k, input);
	else {
		k++;
		construct_candidates(a, k, input, c, &ncandidates);
		for (i=0; i < ncandidates; i++) {
			a[k] = c[i];
			backtrack(a, k, input);
			if (finished) return;	/* terminate early */
		}
	}
}

int is_a_solution(int a[], int k, data in){
	/* (k+1) é a qtd de bispos */
	#ifdef DEBUG
	printf("\tis result? %d == %d\n", (k+1), in.k_bis);
	#endif
	return (k+1) == in.k_bis;
}

long long int sol = 0;
void process_solution(int a[], int k, data in){
	//~ #ifdef DEBUG
	printf("\tresult #%lld", sol);
	printf("\tBISPOS { ");
	for (int i=0; i <= k; i++){
		printf("%d, ", a[i]);
	}
	printf("}\n");
	//~ #endif
	sol++;
}

int isDiagonal(int src, int dest, int boardSize){
	int ax, ay, bx, by;
	
	ax = src / boardSize; // linha
	ay = src % boardSize; // coluna
	
	bx = dest / boardSize; // linha
	by = dest % boardSize; // coluna
	
	if (ax-ay == bx-by || ax+ay == bx+by){
		return 1;
	}
	return 0;
}

void construct_candidates(int a[], int k, data in, int cand[], int *ncandidates){
	#ifdef DEBUG
	int i;
	printf("\tconstruct_candidates(k %d)\n", k);
	printf("\t\tBISPOS { ");
	for (i=0; i < k; i++){
		printf("%d, ", a[i]);
	}
	printf("}\n");
	#endif
	
	int POSICOES, BISPO_PARA_ALOCAR;
	int ntab = in.n_tab;
	POSICOES = ntab * ntab;
	BISPO_PARA_ALOCAR = in.k_bis - k;
	
	int casela, bispo;	/* counters */
	int legal_move;		/* might the move be legal? */
	*ncandidates = 0;
	
	// para cada uma das casas
	for (casela = a[k]; casela < POSICOES; casela++) {
		legal_move = 1;
		
		/* se não tiver opções restantes o suficiente pra alocar o resto dos bispos, ignora */
		if ( (POSICOES - casela) - BISPO_PARA_ALOCAR < 0){
			#ifdef DEBUG
			printf("\tFINALIZANDO POR FALTA DE ESPACO PARA OS BISPOS\n");
			#endif
			break;
		}
		
		// para cada um dos bispos
		for (bispo = 0; bispo < k; bispo++) {
			if ( isDiagonal(casela, a[bispo], ntab) ){
				legal_move = 0;
				break;
			}
		}
		
		if (legal_move == 1) {
			cand[*ncandidates] = casela;
			(*ncandidates)++;
		}
	}
	
	#ifdef DEBUG
	printf("\t candidatos { ");
	for (i=0; i<*ncandidates; i++){
		printf("%d, ", cand[i]);
	}
	printf("}\n");
	#endif
}

void bishops(int k, int n){
	data input;
	input.k_bis = k;
	input.n_tab = n;
	int a[MAXCANDIDATES], i;
	sol = 0;
	for (i = 0; i < MAXCANDIDATES; i++){
		a[i] = 0;
	}
	backtrack(a, -1, input);
	printf("F(k_bis, n_tab) (%d, %d) = %lld\n", k, n, sol);
}

int main(int argc, char **argv){
	bishops(2,2);
	bishops(3,3);
	#ifndef DEBUG
	bishops(3,4);
	bishops(4,4);
	#endif
	return 0;
}
