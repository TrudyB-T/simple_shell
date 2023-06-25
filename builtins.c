#include "prototypes.h"

/**
 * search_builtin - searches for builtins
 * @argv: the string to be used
 * Return: on success >=1, on failure -1
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
			return (k + 1);
		k++;
	}
	return (-1);
}

/**
 * exec_builtins - execute builtin functions
 * @argv: argument vector
 * @k: index
 */
void exec_builtins(char **argv, int k)
{
	switch (k)
	{
		case 1:
			_exit_(argv);
			break;
		case 4:
			_printenv();
			break;

		default:
			break;
	}
}
