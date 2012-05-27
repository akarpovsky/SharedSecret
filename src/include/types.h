#if !defined(TYPES_H)
#define TYPES_H

#include <stdbool.h>

typedef char *String;

typedef struct
{
	bool distribution;
	String secret;
	int k;
} Params;

#endif