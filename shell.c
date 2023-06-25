#include "prototypes.h"

/**
 * main - a simple shell interpreter
 * @argc: argument count
 * @argv: argument vector
 * @env: environment
 * Return: 0 means success
 */
int main(int argc, char **argv, char **env)
{
	char *str = (":)trukel$ ");
	char *line = NULL;
	int len = _strlen(str);
	int bufsize = BUFFER_LEN;
	struct stat fileinfo;
	(void) argc;
	(void) env;


	while (1)
	{
		if (isatty(STDIN_FILENO))
			
			write(STDOUT_FILENO, str ,len);

		line = _getline();

		argv = tokenize(line, bufsize);

		if (argv == NULL || argv[0] == NULL)
		{
			execute(argv);
		}
		else
		{
			if (stat(argv[0], &fileinfo) != 0)
			{
				argv[0] = locate_command(argv[0]);
			}
			execute(argv);
		}
	}
	return (0);
}
