#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include "imageLoader.h"
#include "gauss.h"
#include <math.h>

#define PRIME 251

int
distribution(BmpImage secret, BmpImage * cover, int k, int n);

#endif