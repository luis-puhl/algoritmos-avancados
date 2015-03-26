#include <stdio.h>
#include <stdlib.h>
//~ #include <cmath>
using namespace std;
#define MAXCANDIDATES 64
//~ #define DEBUG
int finished = 0;		/* found all solutions yet? */
typedef struct{
	int k_bis;
	int n_tab;
} data;

//~ void construct_candidates(int[], int, data, int[], int*);
//~ void construct_candidates(int a[], int k, data in, int cand[], int nCand*, int prevCand[]);
int* construct_candidates(int a[], int k, data in, int prevCand[]);
int is_a_solution(int[], int, data);
void process_solution(int[], int, data);

void backtrack(int a[], int k, data input, int prevCand[]);

void backtrack(int a[], int k, data input){
	int *prevCand;
	int i;
	prevCand = (int*) malloc(sizeof(int) * input.n_tab*input.n_tab);
	for (i = 0; i < input.n_tab*input.n_tab; i++){
		printf("putting %d on preCand\n", i);
		prevCand[i] = i;
	}
	printf("sizeof preCand = %ld\n", sizeof(prevCand) / sizeof(int));
	backtrack(a, k, input, prevCand);
}

void backtrack(int a[], int k, data input, int prevCand[]){
	//~ int c[MAXCANDIDATES];	/* candidates for next position */
	int ncandidates;		/* next position candidate count */
	int i;					/* counter */
	int *c;
	
	if (is_a_solution(a, k, input))
		process_solution(a, k, input);
	else {
		k++;
		ncandidates = sizeof(prevCand) / sizeof(int);
		#ifdef DEBUG
		printf("\t\tbacktrack_prevCand { ");
		for (i=0; i < ncandidates; i++){
			printf("%d, ", prevCand[i]);
		}
		printf("}\n");
		#endif
		for (i=0; i < ncandidates; i++) {
			#ifdef DEBUG
			printf("\tk= %d, i= %d\n", k, i);
			#endif
			a[k] = prevCand[i];
			c = construct_candidates(a, k, input, prevCand);
			backtrack(a, k, input, c);
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
	#if  defined (DEBUG) || defined (SHOW_RESULT)
	printf("\tresult #%lld", sol);
	printf("\tBISPOS { ");
	for (int i=0; i <= k; i++){
		printf("%d, ", a[i]);
	}
	printf("}\n");
	#endif
	sol++;
}

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

int* construct_candidates(int a[], int k, data in, int prevCand[]){
	int* cand = (int*) malloc(sizeof(prevCand));
	
	int ncandidates;
	int prevCandSize = sizeof(prevCand) / sizeof(int);
	int bispo = a[k];
	
	#ifdef DEBUG
	int i;
	printf("\tconstruct_candidates(k %d)\n", k);
	
	printf("\t\tBISPOS { ");
	for (i=0; i < k; i++){
		printf("%d, ", a[i]);
	}
	printf("}\n");
	
	printf("\t\tBISPO = %d\n", bispo);
	
	printf("\t\tprevCand { ");
	for (i=0; i < prevCandSize; i++){
		printf("%d, ", prevCand[i]);
	}
	printf("}\n");
	#endif
	
	(ncandidates) = 0;
	for (int i = 0; i < prevCandSize; i++){
		if ( !isDiagonal(prevCand[i], bispo, in.n_tab) ){
			cand[(ncandidates)++] = prevCand[i];
		}
	}
	int *cand2 = (int*) malloc(ncandidates * sizeof(int));
	for (int i = 0; i < ncandidates; i++){
		cand2[i] = cand[i];
	}
	cand = cand2;
	
	#ifdef DEBUG
	printf("\t candidatos { ");
	for (i=0; i<ncandidates; i++){
		printf("%d, ", cand[i]);
	}
	printf("}\n");
	#endif
	
	return cand;
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
