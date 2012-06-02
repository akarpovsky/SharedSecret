#include <stdlib.h>
#include <stdbool.h>

#include "include/messages.h"
#include "include/cmdline.h"
#include "include/imageLoader.h"
#include "include/distribution.h"

int
main(int argc, char **argv)
{

	struct gengetopt_args_info *args_info = malloc(sizeof(struct gengetopt_args_info));

	if(cmdline_parser(argc, argv, args_info) != 0) {
		return EXIT_FAILURE;
	}

	if(args_info->secret_given) {
		/*BmpImage secret = create_bmp_image(args_info->secret_arg);*/
		BmpImage secret = create_bmp_image("images/secrets/Gustavo.bmp");
		load_bmp_image(secret);
		
		BmpImage c1 = create_bmp_image("images/sub1/Alfred.bmp");
		BmpImage c2 = create_bmp_image("images/sub1/Eva.bmp");
		BmpImage c3 = create_bmp_image("images/sub1/Audrey.bmp");
		BmpImage c4 = create_bmp_image("images/sub1/Albert.bmp");
		load_bmp_image(c1);
		load_bmp_image(c2);
		load_bmp_image(c3);
		load_bmp_image(c4);

		BmpImage p[] = {c1,c2,c3, c4};
		distribution(secret, p, 3, 4);

		save_bmp_image(c1);
		save_bmp_image(c2);
		save_bmp_image(c3);
		save_bmp_image(c4);

		free_bmp_image(secret);
		free_bmp_image(c1);
		free_bmp_image(c2);
		free_bmp_image(c3);
		free_bmp_image(c4);

	}



	free(args_info);

	return EXIT_SUCCESS;
}