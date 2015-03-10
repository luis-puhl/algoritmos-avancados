#include <stdio.h>
typedef int data;
typedef int bool;
#define FALSE 0
#define TRUE 1
#define MAXCANDIDATES 10
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
