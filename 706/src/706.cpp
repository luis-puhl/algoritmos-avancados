#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @return 0 or 1
 */
int ligaSegmento(char numero, int segmento){
	
	switch (numero){
	case '0':
		switch (segmento){
		case 7:
			return 0;
		default:
			return 1;
		}
		break;
	case '1':
		switch (segmento){
		case 2:
		case 3:
			return 1;
		default:
			return 0;
		}
		break;
	case '2':
		switch (segmento){
		case 1:
		case 2:
		case 4:
		case 5:
		case 7:
			return 1;
		default:
			return 0;
		}
		break;
	case '3':
		switch (segmento){
		case 1:
		case 2:
		case 3:
		case 4:
		case 7:
			return 1;
		default:
			return 0;
		}
		break;
	case '4':
		switch (segmento){
		case 2:
		case 3:
		case 6:
		case 7:
			return 1;
		default:
			return 0;
		}
		break;
	case '5':
		switch (segmento){
		case 2:
		case 5:
			return 0;
		default:
			return 1;
		}
		break;
	case '6':
		switch (segmento){
		case 2:
			return 0;
		default:
			return 1;
		}
		break;
	case '7':
		switch (segmento){
		case 1:
		case 2:
		case 3:
			return 1;
		default:
			return 0;
		}
		break;
	case '8':
		return 1;
	case '9':
		switch (segmento){
		case 5:
			return 0;
		default:
			return 1;
		}
		break;
	}
	
	return 0;
}

int printNumbers(int size, char *number){
	int linha, sizeAux;
	int numberAux, col, colAux, strlen_number;
	int segmento;
	char result;
	
	strlen_number = strlen(number);
	// numeroDeColunas = (2 + size) * strlen_number;
	
	for (linha = 0; linha < 5; linha++){
		
		if ( linha == 1 || linha == 3){
			sizeAux = size;
		} else {
			sizeAux = 1;
		}
		
		// repete as linhas 1 e 3
		for ( ; sizeAux >= 1; sizeAux--){
			//~ printf("linha %d", linha);
			
			// para cada numero
			for (numberAux = 0; numberAux <= strlen_number; numberAux++){
				//~ printf("char %d\t", numberAux);
				//~ printf("'%c'\t", number[numberAux]);
				
				for (col = 0; col <= 3; col++){
					segmento = 0;
					switch (linha){
						case 0: 
							if (col == 1){
								segmento = 1;
							}
							break;
						case 1:
							switch (col){
								case 0: segmento = 6; break;
								case 3: segmento = 2; break;
							}
							break;
						case 2:
							if (col == 1){
								segmento = 7;
							}
							break;
						case 3:
							switch (col){
								case 0: segmento = 5; break;
								case 3: segmento = 3; break;
							}
							break;
						case 4:
							if (col == 1){
								segmento = 4;
							}
							break;
					}
					
					result = '+';
					if (segmento != 0 && ligaSegmento(number[numberAux], segmento) ){
						if ( linha == 0 || linha == 2 || linha == 4){
							result = '-';
						} else {
							result = '|';
						}
					} else {
						result = ' ';
					}
					
					// repete as colunas internas
					if (col == 1){
						for (colAux = 0; colAux < size; colAux++){
							printf("%c", result);
						}
					} else {
						printf("%c", result);
					}
				}
				
				if (numberAux != strlen_number){
					printf(" ");
				}
				
			}
			
			printf("\n");
		}
	}
	
	return 0;
}

int main(int argc, char **argv){
	char number[9];
	int size;
	long numberAtol;
	
	while (scanf("%d %ld", &size, &numberAtol) != EOF){
		sprintf(number, "%ld", numberAtol);
		if (size == 0 && numberAtol == 0){
			break;
		}
		
		printNumbers(size, number);
		
		printf("\n");
	}
	
	return 0;
}

