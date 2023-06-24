#include "prototypes.h"

/**
 * execute - execute input commands
 * @argv: argument  vector
 *
 * Return: Always 0
 */

int execute(char **argv)
{
	pid_t cp;
	ssize_t val;

	cp = fork();

	if (cp == 0)
	{
		val = execve(argv[0], argv, NULL);

		if (val == -1)
		{
			perror("./hsh");
			exit(0);
		}
	}

	else if (cp < 0)
	{
		perror("./hsh error: child is -1");
		exit(-1);
	}

	else
	{
		wait(NULL);
	}
	return (0);

}
