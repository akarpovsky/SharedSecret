#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <stdio.h>
#include <stdlib.h>
#include "messages.h"

struct bmp_image {
	char *filename;
	int width;
	int height;
	short pixel_bits;
	int compression_method;
	int image_size;

	void *header;
	void *bitmap;
};

typedef struct bmp_image * BmpImage;

BmpImage create_bmp_image(char * filename);

int load_bmp_image(BmpImage image);

void free_bmp_image(struct bmp_image* im);


#endif