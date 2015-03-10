/*

 Problem B: Minesweeper 

The Problem

Have you ever played Minesweeper? It's a cute little game which 
comes within a certain Operating System which name we can't really 
remember. Well, the goal of the game is to find where are all the 
mines within a MxN field. To help you, the game shows a number in a 
square which tells you how many mines there are adjacent to that 
square. For instance, supose the following 4x4 field with 2 mines 
(which are represented by an * character):

*...
....
.*..
....
If we would represent the same field placing the hint numbers described above, we would end up with:
*100
2210
1*10
1110
As you may have already noticed, each square may have at most 8 adjacent squares.
The Input

The input will consist of an arbitrary number of fields. The first 
line of each field contains two integers n and m (0 < n,m <= 100) 
which stands for the number of lines and columns of the field 
respectively. The next n lines contains exactly m characters and 
represent the field. Each safe square is represented by an "." 
character (without the quotes) and each mine square is represented 
by an "*" character (also without the quotes). The first field line 
where n = m = 0 represents the end of input and should not be 
processed.

The Output

For each field, you must print the following message in a line alone:

Field #x:

Where x stands for the number of the field (starting from 1). The 
next n lines should contain the field with the "." characters 
replaced by the number of adjacent mines to that square. There must 
be an empty line between field outputs.

Sample Input

4 4
*...
....
.*..
....
3 5
**...
.....
.*...
0 0
Sample Output

Field #1:
*100
2210
1*10
1110

Field #2:
**100
33200
1*100



problemas encotrados:
* falta de familiaridade com a linguagem
* 
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>


int **mat;
int n_rows, m_cols;
int field_numb;
char chr;

using namespace std;

int markaMina(int **mat, int row, int col, int max_row, int max_col){
	int i, j, c_row, c_col; // current_row and col
	
	for (i = -1; i <= 1; i++){
		for (j = -1; j <= 1; j++){
			c_row = row + i;
			c_col = col + j;
			if (c_row >= 0 && c_col >= 0 
					&& c_row < max_row && c_col < max_col
					&& mat[c_row][c_col] >= 0){
				mat[c_row][c_col]++;
			}
		}
	}
	
	return 0;
}


int main(int argc, char **argv){
	int i, j;
	
	while (1){
		n_rows = m_cols = 0;
		//~ printf("expecting size\t");
		scanf("%d %d", &n_rows, &m_cols);
		
		if (n_rows == 0 || m_cols == 0){
			//~ printf("end");
			break;
		}
		if (n_rows < 0 || m_cols < 0){
			continue;
		}
		if (m_cols > 100){
			m_cols = 100;
		}
		
		if (field_numb != 0) printf("\n");
		printf("Field #%d:\n", ++field_numb);
		
		mat = (int **) malloc(n_rows * sizeof(int*));
		
		//~ printf("carrega\n");
		for (i = 0; i < n_rows; i++){
			mat[i] = (int *) malloc(m_cols * sizeof(int));
			
			for (j = 0; j < m_cols; j++){
				do {
					scanf("%c", &chr);
				} while(chr != '.' && chr != '*');
				
				mat[i][j] = - (chr == '*');
				//~ printf("read[%d][%d] = %d\n", i, j, mat[i][j]);
			}
		}
		
		//~ printf("computa\n");
		for (i = 0; i < n_rows; i++){
			for (j = 0; j < m_cols; j++){
				if (mat[i][j] == -1){
					markaMina(mat, i, j,n_rows, m_cols);
				}
			}
		}
		
		//~ printf("mostra\n");
		for (i = 0; i < n_rows; i++){
			for (j = 0; j < m_cols; j++){
				if (mat[i][j] < 0){
					printf("*");
				} else {
					printf("%d", mat[i][j]);
				}
			}
			printf("\n");
		}
		
		free(mat);
		//~ printf("\n");
		
	}
	
	
	return 0;
}
