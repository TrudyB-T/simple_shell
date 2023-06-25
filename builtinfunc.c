#include "prototypes.h"

/**
 */

void _exit_(char **argv)
{
	if (argv[1] == NULL)
	{
		free(argv);
		exit(0);
	}

	else
	{
		free(argv);
		exit(_atoi(argv[1]));
	}
}
