#include "include/utils.h"

int
mod(int x, int y)
{
	if(x < 0) {
		return x + ceil(-x/(float)y)*y;
	}else{
		return x % y;
	}
}

void
printBlock(unsigned char * block, int k)
{
	int i;
	for(i = 0; i < k; i++) {
		printf(" %d ", block[i]);
	}
	printf("\n");
}
