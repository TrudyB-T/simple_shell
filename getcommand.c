#include "prototypes.h"

/**
 * _getline - gets the input string from user
 *
 * Return: pointer to the input string
 */


char *_getline(void)
{
	char *lineptr = NULL;
	size_t n = 0;
	int num;


	num = getline(&lineptr, &n, stdin);

	if (num == -1)
	{
		if (isatty(STDIN_FILENO))
			write(1, "\n", 1);
		exit(0);
	}

	lineptr = strtok(lineptr, "\n");

	return (lineptr);
}
