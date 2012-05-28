#include <stdlib.h>
#include <stdbool.h>

#include "include/messages.h"
#include "include/cmdline.h"
#include "include/imageLoader.h"
int
main(int argc, char **argv)
{

	struct gengetopt_args_info *args_info = malloc(sizeof(struct gengetopt_args_info));

	if(cmdline_parser(argc, argv, args_info) != 0) {
		return EXIT_FAILURE;
	}

	if(args_info->secret_given) {
		BmpImage im = create_bmp_image(args_info->secret_arg);
		if(load_bmp_image(im) == 0) {
			printf("Width: %d\n", im->width);
			printf("Height: %d\n", im->height);
			printf("Size: %d\n", im->image_size);
		}else{
			printf("error!\n");
		}
	}



	free(args_info);

	return EXIT_SUCCESS;
}