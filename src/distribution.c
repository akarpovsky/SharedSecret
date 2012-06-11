#include "include/distribution.h"

unsigned char * getBlock(BmpImage im, int block, int k);
unsigned char evaluate(unsigned char * secretBlock, unsigned char * a, int k); 
void setBInBlock(BmpImage im, int b, int k,  unsigned char B);
unsigned char * getAvalues(BmpImage im, int block, int k, bool clean);
int * calculateBbits(int k);
void calculateAndSetHashBit(BmpImage im, int bl, int k);
unsigned char getBvalue(BmpImage im, int bl, int k);
unsigned char calculateHashBit(BmpImage im, int bl, int k);
bool checkHashBit(BmpImage im, int bl, int k);
void checkSolvableCombinations(unsigned char **matrix, int k, int n, int * coverProblems);
void indexCombinations(int *comb, int k, int n, int pos, int *counter, int **combinations);
int fact(int number);
void distributeSecretBlock(BmpImage *cover, unsigned char *secretBlock, int bl, int k, int n, unsigned char **matrix); 
void createSubMatrix(unsigned char **matrix, unsigned char **subMatrix, int *indices, int k);
void fixCover(BmpImage *cover, int * coverProblems, int bl, int k, int n);

int
distribution(BmpImage secret, BmpImage * cover, int k, int n, int verbose)
{

	int maxblocks = (secret->width * secret->height)/k;
	
	unsigned char * secretBlock;
	int bl;

	unsigned char ** matrix = createMatrix(k, n);
	int i;

	if(verbose) {
		printf("0");
		for(i = 2; i < 78; i++) {
			printf(" ");
		}
		printf("100\n");
	}

	fflush(stdout);

	for(bl = 0; bl < maxblocks; bl++) {
		if(verbose && (bl % (maxblocks / 80)) == 0) {
			printf(".");
			fflush(stdout);
		}
		secretBlock = getBlock(secret, bl, k);
		distributeSecretBlock(cover, secretBlock, bl, k, n, matrix);
	}

	if(verbose) {
		printf("\n");
	}

	freeMatrix(matrix, n);

	return 0;
}

void
distributeSecretBlock(BmpImage *cover, unsigned char *secretBlock, int bl, int k, int n, unsigned char **matrix) 
{
	unsigned char B;
	unsigned char * a;
	int c, i;
	int * coverProblems = malloc(n * sizeof(int));
	int round = 0;
	int columnProblem = -1;
	do {
		if(round > 0) {
			fixCover(cover, coverProblems, bl, k, n);
		}
		round++;

		for(c = 0; c < n; c++) {
			a = getAvalues(cover[c], bl, k, false);
			B = evaluate(secretBlock, a, k);

			for(i = 0; i < k; i++) {
				matrix[c][i] = a[i];
			}
			matrix[c][k] = B;
		}
		checkSolvableCombinations(matrix, k, n, coverProblems);
	}while(hasProblems(coverProblems, n));

	for(c = 0; c < n; c++) {
		a = getAvalues(cover[c], bl, k, true);
		B = evaluate(secretBlock, a, k);
		setBInBlock(cover[c], bl, k, B);
		calculateAndSetHashBit(cover[c], bl, k);
	}
}

void
fixCover(BmpImage *cover, int *coverProblems, int bl, int k, int n) {
	int *Bbits = calculateBbits(k);
	int i, pos, cpos, dpos = 0;
	int inc = pow(2,(Bbits[0] + 1));
	unsigned char *block;
	
	/*Cover a modificar*/
	cpos = rand() % k;

	for(i = 0; i < n; i++) {
		if(coverProblems[i] > 0) {
			if(cpos == dpos++) {
				block = getBlock(cover[i], bl, k);
				/* Pixel a modificar */
				pos = rand() % k;
				if((255 - block[pos]) < inc) {
					block[pos] += 200;
				}else{
					block[pos] += inc;
				}
				return;
			}
		}
	}
}

int
hasProblems(int *coverProblems, int n) {
	int i;
	for(i = 0; i < n; i++) {
		if(coverProblems[i] > 0) {
			return true;
		}
	}
	return false;
}

void
checkSolvableCombinations(unsigned char **matrix, int k, int n, int * coverProblems) 
{


	int i,j;
	int *numbers = malloc(n*sizeof(int));
	for(i = 0; i < n; i++) {
		numbers[i] = i;
	}

	/*Se obtienen todas las posibles combinaciones de ecuaciones*/
	int * comb = malloc(k*sizeof(int));
	int c = 0;
	int posComb = fact(n) / ((fact(n-k)*fact(k)));
	int **combinations = malloc(posComb * sizeof(int *));
	for(i = 0; i < posComb; i++) {
		combinations[i] = malloc(k * sizeof(int));
	}
	indexCombinations(comb, k, n, 0, &c, combinations);

	unsigned char **subMatrix = createMatrix(k, k);

	/* Se ponen todos los flags en 0*/
	for(i = 0; i < n; i++){
		coverProblems[i] = 0;
	}
	

	for(i = 0; i < posComb; i++) {
		createSubMatrix(matrix, subMatrix, combinations[i], k);

		if(!scd(subMatrix, k, k)) {
			for(j = 0; j < k; j++) {
				coverProblems[combinations[i][j]] = 1;
			}
			break;
		}
	}


	freeMatrix(subMatrix, k);
}

void
indexCombinations(int *comb, int k, int n, int pos, int *counter, int **combinations)
{
	int i;
	int initV = (pos == 0) ? 0 : (comb[pos - 1] + 1);
	if(pos == k) {
		for(i = 0; i < k; i++) {
			combinations[*(counter)][i] = comb[i];
		}
		*(counter) = *(counter) + 1;
		return;
	}
	for(i = initV; i < (n - k + 1 + pos); i++) {
		comb[pos] = i;
		indexCombinations(comb, k, n, pos + 1, counter, combinations);
	}
}

int
fact(int number) {
	if(number == 0 || number == 1) {
		return 1;
	}

	int acum = number;
	
	while(number > 1) {
		acum *= --number;
	}
	return acum;
}

void
createSubMatrix(unsigned char **matrix, unsigned char **subMatrix, int *indices, int k) {
	int i, j;
	for(i = 0; i < k; i++) {
		for(j = 0; j < k+1; j++) {
			subMatrix[i][j] = matrix[indices[i]][j];		
		}
	}
}

unsigned char *
getBlock(BmpImage im, int block, int k)
{
	return im->bitmap + (block * k);
}

unsigned char *
getAvalues(BmpImage im, int b, int k, bool clean)
{
	int i;
	
	unsigned char *ret = malloc(k*sizeof(unsigned char));
	unsigned char *block = getBlock(im, b, k);
	int *Bbits = calculateBbits(k);
	int aux;
	unsigned char cleanBlock;
	for(i = 0; i < k; i++) {
		/* Se saca tmb el lugar donde se pone p, se
		pone en el primer pixel como dice el enunciado */
		aux = pow(2, i != 0 ? Bbits[i] : Bbits[i] + 1);
		cleanBlock = block[i] & (256 - aux);
		if(clean) {
			block[i] = cleanBlock;
		}
		ret[i] = (cleanBlock / aux);
	}

	return ret;
}

int *
calculateBbits(int k) {
	int i;
	int * ret = malloc(k*sizeof(int));
	int l, u, previous_l, previous_b, aux;
	for(i = 0; i < k; i++) {
		l = i == 0 ? 8 : (previous_l - previous_b);
		u = k - i;
		ret[i] = previous_b = ceil(l/(float)u);
		previous_l = l;
	}

	/* Se lo da vuelta para hacer como el enunciado */
	for(i = 0; i < k/2; i++) {
		aux = ret[i];
		ret[i] = ret[k - 1 - i];
		ret[k - 1 - i] = aux;
	}

	return ret;
}

void
setBInBlock(BmpImage im, int b, int k,  unsigned char B) {

	unsigned char * curr = getBlock(im, b, k);
	int * Bbits = calculateBbits(k);
	int i, s, shift;
	unsigned char mask, marks;
	for(i = 0; i < k; i++) {
		shift = 0;
		/* Se generan las cantidad de palotes */
		marks = (pow(2, Bbits[i]) - 1);
		for(s = i + 1; s < k; s++) {
			shift += Bbits[s];
		}
		/* Se colocan los palotes para extraer la parte de B que corresponde */
		mask = marks;
		mask = mask << shift;
		/* Se colocan los bits */
		curr[i] |= ((B & mask) >> shift);
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

unsigned char
calculateHashBit(BmpImage im, int bl, int k) {
	unsigned char * hash;
	unsigned char * block = getBlock(im, bl, k);
	hash = MD5((const unsigned char *) getBlock(im, bl, k), k*sizeof(unsigned char), NULL);
	int i, j, pos;
	unsigned char p;

	for(i = 0; i < MD5_DIGEST_LENGTH; i++) {
		for(j = 0; j < 8; j++) {
			if(i == 0 && j == 0) {
				p = hash[0] & 0x01;
			}else{
				pos = pow(2, j);
				p = (p ^ ((pos & hash[i]) >> j));
			}
		}
	}

	return p;
}

void
calculateAndSetHashBit(BmpImage im, int bl, int k) {
	int * Bbits = calculateBbits(k);
	unsigned char * block = getBlock(im, bl, k);
	unsigned char p = calculateHashBit(im, bl, k);
	int p_pos = Bbits[0];
	block[0] |= (p << p_pos);
}

bool
checkHashBit(BmpImage im, int bl, int k) 
{
	int * Bbits = calculateBbits(k);
	int p_pos = Bbits[0];	
	unsigned char *block = getBlock(im, bl, k);
	unsigned char mask = (1 << p_pos);
	unsigned char pbit = (block[0] & mask) >> p_pos;
	/*printf("B:%d, pBit:%d, cBit:%d\n ", block[0], pbit, calculateHashBit(im, bl, k));*/
	block[0] = block[0] & ~mask;
	return calculateHashBit(im, bl, k) == pbit;
}

unsigned char
getBvalue(BmpImage im, int bl, int k) 
{

	unsigned char B = 0, mask;
	unsigned char * curr = getBlock(im, bl, k);
	int * Bbits = calculateBbits(k);
	int i, s, shift;

	for(i = 0; i < k; i++) {
		shift = 0;
		/* Se generan la cantidad de palotes */
		mask = (pow(2, Bbits[i]) - 1);
		for(s = i + 1; s < k; s++) {
			shift += Bbits[s];
		}

		B |= ((curr[i] & mask) << shift);
	}

	return B;

}

int
recover(BmpImage recover, BmpImage * cover, int k, int n, int verbose) 
{

	if(cover == NULL || recover == NULL) {
		return false;
	}

	int maxblocks = (recover->width * recover->height)/k;
	int bl,c,i,ret = true;
	int bitErr = 0, gaussErr = 0;
	unsigned char B;
	unsigned char * a;
	unsigned char ** matrix = createMatrix(k, n);
	unsigned char * solution = malloc(k * sizeof(unsigned char));

	if(verbose) {
		printf("0");
		for(i = 2; i < 78; i++) {
			printf(" ");
		}
		printf("100\n");
	}

	for(bl = 0; bl < maxblocks; bl++) {
		if(verbose && (bl % (maxblocks / 80)) == 0) {
			printf(".");
			fflush(stdout);
		}
		for(c = 0; c < n; c++) {
			if(!checkHashBit(cover[c], bl, k)) {
				bitErr++;
				ret = false;
			}
			/* Se obtienen los valores de a */
			a = getAvalues(cover[c], bl, k, false);
			/* Se obtiene B */
			B = getBvalue(cover[c], bl, k);
			/* Se colocan los valores en la matriz */
			for(i = 0; i < k; i++) {
				matrix[c][i] = a[i];
			}
			matrix[c][k] = (unsigned char) B;
		}

		if(solve(matrix, k, n, solution) == true) {
			for(i = 0; i < k; i++) {
				recover->bitmap[bl*k + i] = solution[i];
			}
		}else{
			gaussErr++;
			ret = false;
		}
	}

	if(verbose) {
		printf("\n");
	}

	if(bitErr > 0) {
		fprintf(stderr, "There were %d authentication errors.\n", bitErr);
	}

	if(gaussErr > 0) {
		fprintf(stderr, "There were %d incompatible systems.\n", gaussErr);
	}

	return ret;

}