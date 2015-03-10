#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXCANDIDATES 64
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
	
	if (is_a_solution(a,k,input))
		process_solution(a,k,input);
	else {
		k = k+1;
		construct_candidates(a,k,input,c,&ncandidates);
		for (i=0; i<ncandidates; i++) {
			a[k] = c[i];
			backtrack(a,k,input);
			if (finished) return;	/* terminate early */
		}
	}
}

int is_a_solution(int a[], int k, data in){
	return k == in.k_bis;
}

long long int sol = 0;
void process_solution(int a[], int k, data in){
	sol++;
}

int isDiagonal(int src, int dest, int boardSize){
	if ( fmod( fabs(src-dest) / (boardSize + 1) , 1 ) == 0 || 
		 fmod( fabs(src-dest) / (boardSize - 1) , 1 ) == 0 ){
		return 1;
	}
	return 0;
}

int test_isDiagonal(){
	int src, dest, boardSize;
	for (boardSize = 3; boardSize <= 3; boardSize++){
		for (src = 0; src <= boardSize*boardSize; src++){
			for (dest = 0; dest < boardSize*boardSize; dest++){
				printf(
					"isDiagonal(src = %d, dest = %d, boardSize = %d) = %d\n",
					src, dest, boardSize, isDiagonal(src, dest, boardSize)
				);
			}
		}
	}
	return 0;
}


void construct_candidates(int a[], int k, data in, int cand[], int *ncandidates){
	//~ printf("\tconstruct_candidates(k %d)\n", k);
	int i,j;
	/* counters */
	int legal_move;
	/* might the move be legal? */
	*ncandidates = 0;
	// para cada uma das casas
	int ntab = in.n_tab;
	for (i=0; i < ntab * ntab; i++) {
		legal_move = 1;
		// para cada um dos bispos
		for (j=0; j<k; j++) {
			// diagonais
			//~ if ( (abs(x-a) % (n + 1)) == 0){
			//~ if ( (abs(i-a[j]) % (ntab + 1)) == 0){
			if ( isDiagonal(i, a[j], ntab) ){
				legal_move = 0;
				break;
			}
		}
		if (legal_move == 1) {
			cand[*ncandidates] = i;
			(*ncandidates)++;
		}
	}
	//~ printf("\t candidatos { ");
	//~ for (i=0; i<*ncandidates; i++){
		//~ printf("%d, ", cand[i]);
	//~ }
	//~ printf("}\n");
}

void bishops(int k, int n){
	data input;
	input.k_bis = k;
	input.n_tab = n;
	int a[MAXCANDIDATES];
	backtrack(a, 0, input);
	printf("F(k_bis, n_tab) (%d, %d) = %lld\n", k, n, sol);
}

int main(int argc, char **argv){
	test_isDiagonal();
	return 0;
	
	bishops(2,2);
	bishops(3,3);
	bishops(3,4);
	bishops(4,4);
	return 0;
}

