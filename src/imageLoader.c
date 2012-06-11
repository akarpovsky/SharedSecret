#include "include/imageLoader.h"

#define THROW_FILE_ERROR return 1
#define FCHK(x) if((x) != 1) {THROW_FILE_ERROR;}

BmpImage
create_bmp_image(char * filename)
{
	BmpImage ret = malloc(sizeof(struct bmp_image));
	ret->filename = malloc(strlen(filename) + 1);
	strcpy(ret->filename, filename);

	return ret;
}

int 
load_bmp_image(BmpImage im)
{
	FILE *fp;
	int array_offset;
	
	fp = fopen(im->filename, "rb");

	if(fp == NULL) {
		THROW_FILE_ERROR;
	}

	fseek(fp, 10, SEEK_SET);
	FCHK(fread(&array_offset, 4, 1, fp));

	/*Se copia el header entero para guardarlo como estaba*/
	im->header_size = array_offset;
	im->header = malloc(im->header_size);
	fseek(fp, 0x00, SEEK_SET);
	FCHK(fread(im->header, im->header_size, 1, fp));

	fseek(fp, 0x12, SEEK_SET);
	FCHK(fread(&(im->width), sizeof(im->width), 1, fp));

	fseek(fp, 0x16, SEEK_SET);
	FCHK(fread(&(im->height), sizeof(im->height), 1, fp));

	fseek(fp, 0x1C, SEEK_SET);
	FCHK(fread(&(im->pixel_bits), sizeof(im->pixel_bits), 1, fp));

	fseek(fp, 0x22, SEEK_SET);
	FCHK(fread(&(im->image_size), sizeof(im->image_size), 1, fp));

	im->bitmap = malloc(im->image_size);
	fseek(fp, im->header_size, SEEK_SET);
	FCHK(fread(im->bitmap, im->image_size, 1, fp));

	fclose(fp);
	return 0;
}

int
save_bmp_image(BmpImage im) 
{
	FILE *fp;
	fp = fopen(im->filename, "wb");

	if(fp != NULL) {
		fseek(fp, 0x00, SEEK_SET);
		FCHK(fwrite(im->header, im->header_size, 1, fp));
		FCHK(fwrite(im->bitmap, im->image_size, 1, fp));

		fclose(fp);
		return true;
	}
	return false;
}

void
free_bmp_image(struct bmp_image* im)
{
	free(im->header);
	free(im->bitmap);
}

BmpImage 
duplicate(BmpImage im, char * filename) {
	BmpImage ret = malloc(sizeof(struct bmp_image));

	ret->filename = filename;
	ret->width = im->width;
	ret->height = im->height;
	ret->pixel_bits = im->pixel_bits;
	ret->image_size = im->image_size;
	ret->header_size = im->header_size;
	ret->header = malloc(im->header_size);
	ret->bitmap = malloc(im->image_size);
	memcpy(ret->header, im->header, im->header_size);
	memcpy(ret->bitmap, im->bitmap, im->image_size);

	return ret;
}

void 
print_bmp_image(BmpImage im) {
	printf("Width: %d\n", im->width);
	printf("Height: %d\n", im->height);
	printf("Pixel_bits: %d\n", im->pixel_bits);
	printf("Size: %d\n", im->image_size);
	printf("Header size: %d\n", im->header_size);
}