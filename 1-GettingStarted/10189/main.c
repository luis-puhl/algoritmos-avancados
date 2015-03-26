#include <stdio.h>
#include <stdlib.h>

/**
 * submission id 15223487
 */
int **mat;
int n_rows, m_cols;
int field_numb;
char chr;

int markaMina(int **mat, int row, int col, int max_row, int max_col){
	int i, j, c_row, c_col;
	
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
		scanf("%d %d", &n_rows, &m_cols);
		
		if (n_rows == 0 || m_cols == 0){
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
		
		for (i = 0; i < n_rows; i++){
			mat[i] = (int *) malloc(m_cols * sizeof(int));
			
			for (j = 0; j < m_cols; j++){
				do {
					scanf("%c", &chr);
				} while(chr != '.' && chr != '*');
				
				mat[i][j] = - (chr == '*');
			}
		}
		
		for (i = 0; i < n_rows; i++){
			for (j = 0; j < m_cols; j++){
				if (mat[i][j] == -1){
					markaMina(mat, i, j,n_rows, m_cols);
				}
			}
		}
		
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
	}
	
	
	return 0;
}
