#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
	int i, j;
	char mat[102][102];
	int n_rows, m_cols;
	int row, col;
	int field_numb = 0;
	char chr;
	
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
		
		memset(mat, 0, (mat[n_rows+1][m_cols+1] - mat[0][0]) );
		
		for (row = 0; row < n_rows; row++){
			for (col = 0; col < m_cols; col++){
				do {
					chr = getchar();
				} while(chr != '.' && chr != '*');
				
				if (chr == '*'){
					if (row-1 >= 0){
						if (col-1 >= 0){
							mat[row-1][col-1]++;
						}
						mat[row-1][col]++;
						if (col+1 < m_cols){
							mat[row-1][col+1]++;
						}
					}
					if (col-1 >= 0){
						mat[row][col-1]++;
					}
					mat[row][col] = -10;
					if (col+1 < m_cols){
						mat[row][col+1]++;
					}
					if (row+1 < n_rows){
						if (col-1 >= 0){
							mat[row+1][col-1]++;
						}
						mat[row+1][col]++;
						if (col+1 < m_cols){
							mat[row+1][col+1]++;
						}
					}
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
	}
	
	printf("\nendp\n");
	
	return 0;
}
