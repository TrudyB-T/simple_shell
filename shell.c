#include "prototypes.h"

/**
 * main - Entry point
 * @argc: argument count
 * @argv: argument vector
 * @env: environment
 * Return: nothing
 */

int main(int argc, char **argv, char **env)
{
	char *str = "trukel$ ";
	char *line;
	int bufsize = BUFFER_LEN;
	(void) argc;
	(void) env;


	while (1)
	{
		if (isatty(STDIN_FILENO))

			write(STDOUT_FILENO, str, 8);

		line = _getline();

		argv = tokenize(line, bufsize);

		execute(argv);
	}
	return (0);
}
