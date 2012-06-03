#include "include/gauss.h"

unsigned char * createModuleMap();
void mulRow(unsigned char **matrix, int k, int row, int num);
void subRowNTimes(unsigned char **matrix, int k, int currentRow, int rowToSub, int times);

unsigned char ** 
createMatrix(int k, int n)
{
	unsigned char **matrix = malloc(n * sizeof(unsigned char));
	int i;
	for(i = 0; i < n; i++) {
		matrix[i] = malloc((k + 1) * sizeof(unsigned char));
	}
	return matrix;
}

void
freeMatrix(unsigned char ** matrix, int n)
{
	int i;
	for(i = 0; i < n; i++) {
		free(matrix[i]);
	}
	free(matrix);
}

int
solve(unsigned char **matrix, int k, int n) {

	unsigned char * modmap = createModuleMap();

	int i, j, num;
	for(i = 0; i < n; i++) {
		if(matrix[i][i] != 1) {
			num = modmap[matrix[i][i] - 1];
			mulRow(matrix, k, i, num);
		}
		for(j = 0; j < n; j++) {
			if(i != j && matrix[j][i] != 0) {
				subRowNTimes(matrix, k, j, i, matrix[j][i]);
			}
		}
	}

	free(modmap);
	return 0;

}

void
printMatrix(unsigned char **matrix, int k, int n)
{
	int i,j;
	for(i = 0; i < n; i++) {
		for(j = 0; j < k+1; j++) {
			printf(" %d ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

unsigned char *
createModuleMap()
{
	unsigned char * map = malloc(PRIME * sizeof(unsigned char));
	int i, j;
	for(i = 1; i < PRIME + 1; i++) {
		for(j = 1; j < PRIME + 1; j++) {
			if(i * j % PRIME == 1) {
				map[i-1] = j;
				break;
			}
		}
	}
	return map;
}

void
subRowNTimes(unsigned char **matrix, int k, int currentRow, int rowToSub, int times) {
	/*printf("Resta a fila %d la fila %d, %d veces\n", currentRow, rowToSub, times);*/
	int i;
	for(i = 0; i < k + 1; i++) {
		matrix[currentRow][i] = (matrix[currentRow][i]- (times * matrix[rowToSub][i])) % PRIME;
	}
}

void
mulRow(unsigned char **matrix, int k, int row, int num) {
	int i;
	for(i = 0; i < k+1; i++) {
		matrix[row][i] = (matrix[row][i] * num) % PRIME;
	}
}