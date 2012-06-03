#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include <math.h>
#include "imageLoader.h"
#include "gauss.h"
#include "utils.h"

int
distribution(BmpImage secret, BmpImage * cover, int k, int n);

#endif