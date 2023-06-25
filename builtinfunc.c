#include "prototypes.h"

/**
 * _exit_ - executes the exit builtin
 * @argv: the string to be executed
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
