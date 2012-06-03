#include "include/gauss.h"

unsigned char * createModuleMap();
void mulRow(unsigned char **matrix, int k, int row, int num);
void subRowNTimes(unsigned char **matrix, int k, int currentRow, int rowToSub, int times);
int reacomodateMatrix(unsigned char **matrix, int k, int n);
void switchRows(unsigned char **matrix, int k, int row1, int row2);

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
solve(unsigned char **matrix, int k, int n, unsigned char * solution) {

	unsigned char * modmap = createModuleMap();

	if(!reacomodateMatrix(matrix, k, n)) {
		return false;
	}

	int i, j, num;
	for(i = 0; i < n; i++) {
		if(matrix[i][i] != 1 ) {
			num = modmap[matrix[i][i] - 1];
			mulRow(matrix, k, i, num);
		}
		for(j = 0; j < n; j++) {
			if(i != j && matrix[j][i] != 0) {
				subRowNTimes(matrix, k, j, i, matrix[j][i]);
			}
		}
	}

	for(i =0; i < k; i++) {
		if(matrix[i][i] != 1) {
			return false;
		}
		solution[i] = matrix[i][k];
	}

	printf("Solution: ");
	printSolution(solution, k);
	printf("\n\n");

	free(modmap);

	return true;

}

void
printSolution(unsigned char * solution, int k)
{
	int i;
	for(i = 0; i < k; i++) {
		printf(" %d ", solution[i]);
	}
	printf("\n");
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
			if(mod(i * j, PRIME) == 1) {
				map[i-1] = j;
				break;
			}
		}
	}
	return map;
}

void
subRowNTimes(unsigned char **matrix, int k, int row1, int row2, int times) {
	int i;
	int aux;
	for(i = 0; i < k + 1; i++) {
		matrix[row1][i] = mod((matrix[row1][i] - (times * matrix[row2][i])), PRIME);
	}
}

void
mulRow(unsigned char **matrix, int k, int row, int num) 
{
	int i;
	for(i = 0; i < k + 1; i++) {
		matrix[row][i] = mod((matrix[row][i] * num), PRIME);
	}
}

int
reacomodateMatrix(unsigned char **matrix, int k, int n)
{
	int i,j, switchpos;
	for(i = 0; i < k; i++) {
		if(matrix[i][i] == 0) {
			switchpos = -1;
			for(j = i + 1; i < n; i++) {
				if(matrix[i][n] != 0) {
					switchpos = j;
					break;
				}
			}
			if(switchpos == -1) {
				return false;
			}
			switchRows(matrix, k, i, j);
 		}
	}
	return true;
}

void
switchRows(unsigned char **matrix, int k, int row1, int row2)
{
	int i;
	unsigned char aux;
	for(i = 0; i < k+1; i++) {
		aux = matrix[row1][i];
		matrix[row1][i] = matrix[row2][i];
		matrix[row2][i] = aux;
	}
}