#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "include/types.h"
#include "include/cmdline.h"

int
main(int argc, char **argv)
{

	struct gengetopt_args_info args_info;

	if(cmdline_parser(argc, argv, &args_info) != 0) {
		return 1;
	}

	

	return 0;
}