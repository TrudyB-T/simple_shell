#include "prototypes.h"

/**
 */


int search_builtin(char *argv)
{
	int k = 0;
	char *cmd[4];

	cmd[0] = "exit";
	cmd[1] = "cd";
	cmd[2] = "help";
	cmd[3] = "env";

	while (k < 4)
	{
		if (_strcmp(argv, cmd[k]) == 0)
			return(k + 1);

		k++;
	}
	return (-1);
}


/**
 */

void exec_builtins(char **argv, int k)
{
	switch (k)
	{
		case 1:
			_exit_(argv);
			break;
		default:
			break;
	}
}
