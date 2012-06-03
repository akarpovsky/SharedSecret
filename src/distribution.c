#include "include/distribution.h"

char * getBlock(BmpImage im, int block, int k);
unsigned char evaluate(unsigned char * secretBlock, unsigned char * a, int k); 
void setBInBlock(BmpImage im, int b, int k,  unsigned char B);

unsigned char * getAvalues(BmpImage im, int block, int k);
int * calculateBbits(int k);

int
distribution(BmpImage secret, BmpImage * cover, int k, int n)
{

	int maxblocks = secret->image_size/k;
	
	unsigned char * secretBlock;

	int bl,c,B,i;

	unsigned char * a;

	unsigned char ** matrix = createMatrix(k, n);
	unsigned char * solution = malloc(k * sizeof(unsigned char));

	for(bl = 0; bl < maxblocks; bl++) {
		secretBlock = getBlock(secret, bl, k);
		for(c = 0; c < n; c++) {
			a = getAvalues(cover[c], bl, k);
			B = evaluate(secretBlock, a, k);
			for(i = 0; i < k; i++) {
				matrix[c][i] = a[i];
			}
			matrix[c][k] = (unsigned char) B;
			setBInBlock(cover[c], bl, k, B);
		}
		printf("Secret: ");
		printSolution(secretBlock, k);
		solve(matrix, k, n, solution);
	}

	freeMatrix(matrix, n);

	return 0;
}

char *
getBlock(BmpImage im, int block, int k)
{
	return im->bitmap + (block * k);
}

unsigned char *
getAvalues(BmpImage im, int b, int k)
{
	int i;
	
	unsigned char *ret = malloc(k*sizeof(unsigned char));
	unsigned char *block = getBlock(im, b, k);
	int *Bbits = calculateBbits(k);
	int aux;
	for(i = 0; i < k; i++) {
		/* Se saca tmb el lugar donde se pone p */
		aux = pow(2, i != k - 1 ? Bbits[i] : Bbits[i] + 1);
		ret[i] = ((block[i] & (256 - aux)) / aux);
	}

	return ret;
}

int *
calculateBbits(int k) {
	int i;
	int * ret = malloc(k*sizeof(int));
	int l, u, previous_l, previous_b;
	for(i = 0; i < k; i++) {
		l = i == 0 ? 8 : (previous_l - previous_b);
		u = k - i;
		ret[i] = previous_b = ceil(l/(float)u);
		previous_l = l;
	}
	return ret;
}

/*char *
getCoeffAndCleanBlock(BmpImage im, int block, int k)
{
	char * ret = malloc(k * sizeof(char));
	unsigned char *curr = getBlock(im, block, k);
	int i;
	unsigned char aux;
	for(i = 0; i < k; i++) {
		*(curr  + i) &= 0xF8;
		aux = *(curr  + i);
		ret[i] = (aux >> k);
	}
	return ret;
}*/

void
setBInBlock(BmpImage im, int b, int k,  unsigned char B) {

	unsigned char * curr = getBlock(im, b, k);
	int * Bbits = calculateBbits(k);
	int i, s, shift;
	unsigned char mask, marks;
	for(i = 0; i < k; i++) {
		/* Se generan las cantidad de palotes */
		marks = (pow(2, Bbits[i]) - 1);
		for(s = i; s < k; s++) {
			shift += Bbits[s];
		}
		/* Se colocan los palotes para extraer la parte de B que corresponde */
		mask = marks;
		mask << shift;
		/* Se borran los lugares donde voy a poner los bits nuevos */
		*(curr + i) &= ~marks;
		/* Se colocan los bits*/
		*(curr + i) |= ((B & mask) >> shift);
	}

}

unsigned char
evaluate(unsigned char * secretBlock, unsigned char * a, int k) {
	int i;
	int aux = 0;
	for(i = 0; i < k; i++) {
		aux += a[i] * secretBlock[i];
	}
	return aux % PRIME;
}