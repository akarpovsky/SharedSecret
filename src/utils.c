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
