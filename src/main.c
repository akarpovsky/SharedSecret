#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "include/messages.h"
#include "include/cmdline.h"
#include "include/imageLoader.h"
#include "include/distribution.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <err.h>
#include <fts.h>
#include <stdio.h>


#define EXTLEN 4
#define EXT ".bmp"
#define BLOCKSIZE 20 

static int ptree(char * const argv[], int k, int n, char * secretPath);
bool isBmpType(char * filePath);

int
main(int argc, char **argv)
{

	struct gengetopt_args_info *args_info = malloc(sizeof(struct gengetopt_args_info));

	if(cmdline_parser(argc, argv, args_info) != 0) {
		return EXIT_FAILURE;
	}

	if(args_info->secret_given) {
		/*BmpImage secret = create_bmp_image(args_info->secret_arg);*/
		char * path[] = {args_info->dir_arg};
		ptree(path, args_info->keys_arg, args_info->number_arg, args_info->secret_arg);

		// BmpImage secret = create_bmp_image("images/secrets/Gustavo.bmp");
		// load_bmp_image(secret);
		
		// BmpImage c1 = create_bmp_image("images/sub1/Alfred.bmp");
		// BmpImage c2 = create_bmp_image("images/sub1/Eva.bmp");
		// BmpImage c4 = create_bmp_image("images/sub1/Albert.bmp");
		// load_bmp_image(c1);
		// load_bmp_image(c2);
		// load_bmp_image(c4);

		// BmpImage p[] = {c1, c2, c4};
		// distribution(secret, p, 3, 3);

		// save_bmp_image(c1);
		// save_bmp_image(c2);
		// save_bmp_image(c4);

		// free_bmp_image(secret);
		// free_bmp_image(c1);
		// free_bmp_image(c2);
		// free_bmp_image(c4);

	}



	free(args_info);

	return EXIT_SUCCESS;
}

static int
ptree(char * const argv[], int k, int n, char * secretPath)
{
	FTS *ftsp;
	FTSENT *p, *chp;
	int fts_options = FTS_COMFOLLOW | FTS_LOGICAL | FTS_NOCHDIR;
	int rval = 0;
	int amount = 0;
	BmpImage * bmpImages = malloc(BLOCKSIZE * sizeof(BmpImage));

	if ((ftsp = fts_open(argv, fts_options, NULL)) == NULL) {
		warn("fts_open");
		return -1;
	}
/* Initialize ftsp with as many argv[] parts as possible. */
	chp = fts_children(ftsp, 0);
	if (chp == NULL) {
        return 0;               /* no files to traverse */
    }
    while ((p = fts_read(ftsp)) != NULL) {
    	switch (p->fts_info) {
            case FTS_F:
            	if((amount + 1) % BLOCKSIZE == 0){
            		bmpImages = realloc(bmpImages, ((amount) + BLOCKSIZE) * sizeof(BmpImage));
            	}
            	if(isBmpType(p->fts_path) && p->fts_level == 1){
            		BmpImage c1 = create_bmp_image(p->fts_path);
            		load_bmp_image(c1);
            		bmpImages[amount++] = c1;
            		printf("f %s\n", p->fts_path);
            	}
            break;
            
            default:
            break;
        }
    }
    amount--;
    if(amount > 0){
    	BmpImage secret = create_bmp_image(secretPath);
		load_bmp_image(secret);

		int amountOfFiles = n > 0 ? n:amount;

    	distribution(secret, bmpImages, amountOfFiles, k);
    }

    fts_close(ftsp);
    free(bmpImages);
    return 0;
}

bool
isBmpType(char * filePath){
	int currentFilePathLen = strlen(filePath);
	char * currenFilePath = filePath + (currentFilePathLen - EXTLEN);
	return strcmp(currenFilePath, EXT) == 0;
}