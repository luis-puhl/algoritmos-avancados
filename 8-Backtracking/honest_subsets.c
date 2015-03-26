
#include <stdio.h>

typedef int data;
typedef int bool;

#define FALSE 0
#define TRUE 1
#define MAXCANDIDATES 10
#define NMAX 50

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


bool is_a_solution(int a[], int k, int n){
	return (k == n);
}
/* is k == n? */
void construct_candidates(int a[], int k, int n, int c[], int *ncandidates){
	c[0] = TRUE;
	c[1] = FALSE;
	*ncandidates = 2;
}

void process_solution(int a[], int k, data d){
	int i;
	/* counter */
	printf("{");
	for (i=1; i<=k; i++)
	if (a[i] == TRUE) printf(" %d",i);
	printf(" }\n");
}


void generate_subsets(int n){
	int a[NMAX];
	/* solution vector */
	backtrack(a,0,n);
}

int main(int argc, char** argv){
	generate_subsets(3);
	return 0;
}
