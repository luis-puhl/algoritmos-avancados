#include <stdio.h>
#include <stdlib.h>

typedef int data;
typedef int bool;

#define FALSE 0
#define TRUE 1
#define MAXCANDIDATES 100
#define NMAX 500

void construct_candidates(int[], int, data, int[], int*);
bool is_a_solution(int[], int, data);
void process_solution(int[], int, data);

bool finished = FALSE;		/* found all solutions yet? */

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

void construct_candidates(int a[], int k, int n, int c[], int *ncandidates){
	int i,j;			/* counters */
	bool legal_move;	/* might the move be legal? */
	
	*ncandidates = 0;
	
	for (i=1; i<=n; i++) {
		legal_move = TRUE;
		for (j=1; j<k; j++) {
			if (abs((k)-j) == abs(i-a[j])) /* diagonal threat */
				legal_move = FALSE;
			if (i == a[j]) /* column threat */
				legal_move = FALSE;
		}
		if (legal_move == TRUE) {
			c[*ncandidates] = i;
			*ncandidates = *ncandidates + 1;
		}
	}
}

int solution_count = 0;
void process_solution(int a[], int k, data d){
	solution_count ++;
}

bool is_a_solution(int a[], int k, int n){
	return (k == n);
}

void nqueens(int n){
	int a[NMAX]; /* solution vector */
	
	solution_count = 0;
	backtrack(a,0,n);
	printf("n=%d solution_count=%d\n",n,solution_count);
}

int main(int argc, char** argv){
	nqueens(4);
	return 0;
}
