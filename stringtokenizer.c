#include "prototypes.h"

/**
 * tokenize - breaks strings into tokens
 * @ptr: pointer to string
 * @bufsize: buffer size to allocate
 *
 * Return: nothing
 */


char **tokenize(char *ptr, int bufsize)
{
	int k = 0;
	char *tok = NULL;
	char **argv;


	argv = malloc(sizeof(char *) * bufsize);

	if (argv == NULL)
	{
		perror("./hsh");
		free(argv);
		exit(0);
	}

	tok = strtok(ptr, " ");

	while (tok)
	{
		argv[k] = tok;
		tok = strtok(NULL, " ");
		k++;

		if (k >= bufsize)
		{
			bufsize += BUFFER_LEN;

			argv = reallocate(argv, sizeof(argv), bufsize * sizeof(char *));


			if (argv == NULL)
			{
				perror("./hsh");
				exit(0);
			}
		}
	}

	argv[k] = NULL;

	return (argv);
}
