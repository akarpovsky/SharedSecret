#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include <math.h>
#include <openssl/md5.h>
#include <time.h>
#include "imageLoader.h"
#include "gauss.h"
#include "utils.h"

int distribution(BmpImage secret, BmpImage * cover, int k, int n, int verbose);

int recover(BmpImage recover, BmpImage * cover, int k, int n, int verbose);

#endif