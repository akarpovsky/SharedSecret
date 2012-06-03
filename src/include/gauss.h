#ifndef GAUSS_H
#define GAUSS_H

#include <stdlib.h>
#include <stdbool.h>
#include "distribution.h"
#include "utils.h"

unsigned char ** createMatrix(int k, int n);

void freeMatrix(unsigned char ** matrix, int n);

int solve(unsigned char **matrix, int k, int n, unsigned char * solution);

void printMatrix(unsigned char **matrix, int k, int n);

void printSolution(unsigned char * solution, int k);

#endif