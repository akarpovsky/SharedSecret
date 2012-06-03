#ifndef GAUSS_H
#define GAUSS_H

#include <stdlib.h>
#include "distribution.h"

unsigned char ** createMatrix(int k, int n);

void freeMatrix(unsigned char ** matrix, int n);

int solve(unsigned char **matrix, int k, int n);

void printMatrix(unsigned char **matrix, int k, int n);

#endif