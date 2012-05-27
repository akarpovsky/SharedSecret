#include <stdlib.h>
#include <stdbool.h>

#include "include/messages.h"
#include "include/cmdline.h"
#include "include/imageLoader.h"
int
main(int argc, char **argv)
{

	struct gengetopt_args_info args_info;

	if(cmdline_parser(argc, argv, &args_info) != 0) {
		return EXIT_FAILURE;
	}

	BmpImage im = create_bmp_image("images/bmps300x300/cualquiera");

	load_bmp_image(im);

	printf("Width: %d\n", im->width);
	printf("Height: %d\n", im->height);

	return EXIT_SUCCESS;
}

bool
checkFiles(struct gengetopt_args_info * args_info)
{
	if(args_info->number_given) {

	}
}
