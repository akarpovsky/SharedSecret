#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "messages.h"

struct bmp_image {
	char *filename;
	int width;
	int height;
	short pixel_bits;
	int image_size;

	int header_size;

	unsigned char *header;
	unsigned char *bitmap;
};

typedef struct bmp_image * BmpImage;

BmpImage create_bmp_image(char * filename);

int load_bmp_image(BmpImage image);

int save_bmp_image(BmpImage im);

void free_bmp_image(struct bmp_image* im);

BmpImage duplicate(BmpImage im, char * filename);

void print_bmp_image(BmpImage im);

#endif