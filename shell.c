#include "prototypes.h"

/**
 * main - run a simple shell interpreter
 * Return: 0 means success
 */
int main(void)
{
	char *str = (":)trukel$ "), *lineptr = NULL, *line, **argv;
	int len = _strlen(str), k, bufsize = BUFFER_LEN;
	ssize_t num;
	size_t s = 0;
	struct stat fileinfo;

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)

			write(STDOUT_FILENO, str, len);

		num = _getline(&lineptr, &s, stdin);
		if (num == -1)
		{
			exit(-1);
		}
		if (lineptr[num - 1] == '\n')
			lineptr[num - 1] = '\0';
		k = 0;
		while (lineptr[k])
		{
			if (lineptr[k] == '\0')
				lineptr[k] = 0;
			k++;
		}
		line = lineptr;

		argv = tokenize(line, bufsize);
		if (argv == NULL || argv[0] == NULL)
		{
			execute(argv);
		}
		else
		{
			k = search_builtin(argv[0]);
			if (k >= 0)
				exec_builtins(argv, k);
			else
			{
				if (stat(argv[0], &fileinfo) != 0)
					argv[0] = locate_command(argv[0]);
				execute(argv);
			}
		
		}
		free(argv);
	
	}
	free(lineptr);
       return (0);
}
