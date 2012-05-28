#include "include/imageLoader.h"

#define THROW_FILE_ERROR fprintf(stderr, INVALID_BMP, im->filename); return 1
#define FCHK(x) if((x) != 1) {THROW_FILE_ERROR;}

BmpImage
create_bmp_image(char * filename)
{
	BmpImage ret = malloc(sizeof(struct bmp_image));
	ret->filename = filename;
	return ret;
}

int 
load_bmp_image(BmpImage im)
{
	FILE *fp;
	int header_size;
	
	fp = fopen(im->filename, "rb");

	if(fp == NULL) {
		THROW_FILE_ERROR;
	}


	fseek(fp, 0x0E, SEEK_SET);
	FCHK(fread(&header_size, sizeof(header_size), 1, fp));

	/*Se copia el header entero para guardarlo como estaba*/
	im->header_size = 0x0E + header_size;
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
save_bmp_image(BmpImage im) {
	FILE *fp;
	fp = fopen(im->filename, "wb");

	FCHK(fwrite(im->header, im->header_size, 1, fp));
	FCHK(fwrite(im->bitmap, im->image_size, 1, fp));

	fclose(fp);
	return 0;
}

void
free_bmp_image(struct bmp_image* im)
{
	free(im->header);
	free(im->bitmap);
}