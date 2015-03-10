#include <stdio.h>
#include <stdlib.h>
#define MAX_N_TAB	8
#define MAX_K_BISP	(MAX_N_TAB*MAX_N_TAB)

void construct_candidates(int[], int, int[], int*);
int is_a_solution(int[], int);
void process_solution(int[], int);

void backtrack(int bisp[], int iker){
	printf("backtrack(iker %d)\n", iker);
	int possib[MAX_K_BISP];
	int n_possib;
	int i;
	
	if (is_a_solution(bisp, iker)){
		process_solution(bisp, iker);
	} else {
		iker++;
		construct_candidates(bisp, iker, possib, &n_possib);
		for (i = 0; i < n_possib; i++){
			bisp[iker] = possib[i];
			backtrack(bisp, iker);
		}
	}
	
}

int __n_tab;
void construct_candidates(int bisp[], int iker, int possib[], int* n_possib){
	printf("construct_candidates(iker %d)\n", iker);
	
	
	int i,j;			/* counters */
	int legal_move;	/* might the move be legal? */
	
	*n_possib = 0;
	
	for (i=1; i<=n; i++) {
		legal_move = 1;
		for (j=1; j<k; j++) {
			if (abs((k)-j) == abs(i-a[j])) /* diagonal threat */
				legal_move = 0;
		}
		if (legal_move == 1) {
			c[*ncandidates] = i;
			*ncandidates = *ncandidates + 1;
		}
	}
	/*
	int i, b, k, e;
	int tab[__n_tab];
	
	for (b = 0; b < iker; b++){
		tab[bisp[b]] = 1;
		for (k = 0; e<4 && k < __n_tab; k++){
			e = 0;
			int pos[4] = {
				bisp[b] + ( k * __n_tab + k ),
				bisp[b] + ( (-1) * k * __n_tab + k ),
				bisp[b] - ( k * __n_tab + k ),
				bisp[b] - ( (-1) * k * __n_tab + k )
			};
			for (i = 0; i < 4; i++){
				printf("\tpos[%d] = %d\n", i, pos[i]);
				if (pos[i]>=0 && pos[i]<__n_tab){
					tab[pos[i]] = 1;
				} else {
					e++;
				}
			}
		}
		
	}
	
	for (i = 0; i < __n_tab; i++){
		printf("\tn_possib = %d, i = %d\n", *n_possib, i);
		if (tab[i] != 1){
			possib[*n_possib] = i;
			(*n_possib)++;
		}
	}
	*/
}

int __k_bis;
int is_a_solution(int bisp[], int iker){
	printf("is_a_solution iker %d\n", iker);
	return iker == __k_bis;
}

long long int solution_count;
void process_solution(int bisp[], int iker){
	solution_count++;
	printf("process_solution %lld\n", solution_count);
}

void bishops(int k_bis, int n_tab){
	printf("bishops(%d k_bis, %d n_tab)\n", k_bis, n_tab);
	int bisp[k_bis];
	
	__k_bis = k_bis;
	__n_tab = n_tab;
	solution_count = 0;
	
	backtrack(bisp, 0);
	
	printf("F(k_bis, n_tab) (%d, %d) = %lld\n", k_bis, n_tab, solution_count);
}

int main(int argc, char **argv){
	bishops(4, 4);
	return 0;
}

