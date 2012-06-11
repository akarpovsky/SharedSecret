#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <string.h>

#include "include/messages.h"
#include "include/cmdline.h"
#include "include/imageLoader.h"
#include "include/distribution.h"

#define ERRORMSG(x) fprintf(stderr, x); return EXIT_FAILURE

#define MAX_IMAGES 8

char *path_cat (const char *str1, char *str2);

int
main(int argc, char **argv)
{

	struct gengetopt_args_info *args_info = malloc(sizeof(struct gengetopt_args_info));

	if(cmdline_parser(argc, argv, args_info) != 0) {
		return EXIT_FAILURE;
	}

	int i;

	if(args_info->recovery_given) {
		int k = args_info->keys_arg;

		struct dirent *dp;
		char * dirpath = args_info->dir_arg;
		DIR *dir = opendir(dirpath);
		if(dir == NULL) {
			ERRORMSG("The directory doesn't exist or could not be read.\n");
		}

		BmpImage *images = NULL;

		BmpImage aux = create_bmp_image(args_info->secret_arg);
		int n = 0;
		while((dp=readdir(dir)) != NULL && n < MAX_IMAGES) {
			aux->filename = path_cat(dirpath, dp->d_name);
			if(load_bmp_image(aux) == 0) {
				if(args_info->verbose_given) {
					printf("Loaded: %s\n", aux->filename);
				}
				if(images == NULL) {
					images = malloc(sizeof(struct bmp_image));
				}else{
					images = realloc(images, (n + 1) * sizeof(struct bmp_image));
				}
				images[n++] = aux;
				aux = create_bmp_image(args_info->secret_arg);
			}
		}

		if(n < k) {
			ERRORMSG("The number of images (\"n\") must be greater than \"k\".\n");
		}

		BmpImage secret = duplicate(images[0], args_info->secret_arg);

		if(!checkImages(images, secret, n)) {
			ERRORMSG("Incompatible images.\n");
		}

		recover(secret, images, k, n, args_info->verbose_given);

		for(i = 0; i < n; i++) {
			free_bmp_image(images[i]);
		}

		save_bmp_image(secret);
		free_bmp_image(secret);

	}else if(args_info->distribute_given) {
		BmpImage secret = create_bmp_image(args_info->secret_arg);
		if(load_bmp_image(secret) != 0) {
			ERRORMSG("The secret given is not a valid BMP image.\n");
		}
		
		int k = args_info->keys_arg;
		int n = -1;
		if(args_info->number_given) {
			n = args_info->number_arg;
		}

		struct dirent *dp;
		char * dirpath = args_info->dir_arg;
		DIR *dir = opendir(dirpath);
		if(dir == NULL) {
			ERRORMSG("The directory doesn't exist or could not be read.\n");
		}

		BmpImage *images = NULL;

		BmpImage aux = create_bmp_image(args_info->secret_arg);
		int ncounter = 0;
		while((dp=readdir(dir)) != NULL && ncounter != n && ncounter < MAX_IMAGES) {
			aux->filename = path_cat(dirpath, dp->d_name);
			if(load_bmp_image(aux) == 0) {
				if(args_info->verbose_given) {
					printf("Loaded: %s\n", aux->filename);
				}
				if(images == NULL) {
					images = malloc(sizeof(struct bmp_image));
				}else{
					images = realloc(images, (ncounter + 1) * sizeof(struct bmp_image));
				}
				images[ncounter++] = aux;
				aux = create_bmp_image(args_info->secret_arg);
			}
		}

		if(n != -1 && ncounter < n) {
			ERRORMSG("The directory doesn't contains enough images.\n");
		}

		n = ncounter;

		if(n < k) {
			ERRORMSG("The number of images (\"n\") must be greater than \"k\".\n");
		}

		if(!checkImages(images, secret, n)) {
			ERRORMSG("Incompatible images.\n");
		}

		distribution(secret, images, k, n, args_info->verbose_given);

		for(i = 0; i < n; i++) {
			save_bmp_image(images[i]);
			free_bmp_image(images[i]);
		}

		free(images);

		return EXIT_SUCCESS;

	}

	free(args_info);

	return EXIT_SUCCESS;
}

char *path_cat (const char *str1, char *str2) {
	size_t str1_len = strlen(str1);
	size_t str2_len = strlen(str2);
	int needfix = 0;
	if(str1[str1_len - 1] != '/') {
		str1_len += 1;
		needfix = 1;
	}
	char *result;
	result = malloc((str1_len+str2_len+1)*sizeof *result);
	strcpy (result,str1);
	if(needfix == 1) {
		result[str1_len - 1] = '/';
	}
	int i,j;
	for(i=str1_len, j=0; ((i<(str1_len+str2_len)) && (j<str2_len));i++, j++) {
		result[i]=str2[j];
	}
	result[str1_len+str2_len]='\0';
	return result;
}

int
checkImages(BmpImage *images, BmpImage secret, int n) {
	int width = secret->width;
	int height = secret->height;
	int i;
	for(i = 0; i < n; i++) {
		if(images[i]->width != width || images[i]->height != height) {
			return false;
		}
	}
	return true;
}