#include "prototypes.h"

/**
 * get_args - reads input command
 * @line: buffer for command storage
 * @exe_ret: return value previous command
 *
 * Return: NULL
 */
char *get_args(char *line, int *exe_ret)
{
	size_t n = 0;
	ssize_t input;
	char *str = (":)trukel$ ");

	if (line)
		free(line);

	input = _getline(&line, &n, STDIN_FILENO);
	if (input == -1)
		return (NULL);
	if (input == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, str, 10);
		return (get_args(line, exe_ret));
	}

	line[input - 1] = '\0';
	replace_var(&line, exe_ret);
	handle_line(&line, input);

	return (line);
}

/**
 * call_args - spaces commands
 * @argv: argument vector
 * @front: double pointer
 * @exe_ret: return value of parent process
 *
 * Return: return value of the previous command
 */
int call_args(char **argv, char **front, int *exe_ret)
{
	int n, index;

	if (!argv[0])
		return (*exe_ret);
	for (index = 0; argv[index]; index++)
	{
		if (_strncmp(argv[index], "||", 2) == 0)
		{
			free(argv[index]);
			argv[index] = NULL;
			argv = replace_aliases(argv);
			n = run_args(argv, front, exe_ret);
			if (*exe_ret != 0)
			{
				argv = &argv[++index];
				index = 0;
			}
			else
			{
				for (index++; argv[index]; index++)
					free(argv[index]);
				return (n);
			}
		}
		else if (_strncmp(argv[index], "&&", 2) == 0)
		{
			free(argv[index]);
			argv[index] = NULL;
			argv = replace_aliases(argv);
			n = run_args(argv, front, exe_ret);
			if (*exe_ret == 0)
			{
				argv = &argv[++index];
				index = 0;
			}
			else
			{
				for (index++; argv[index]; index++)
					free(argv[index]);
				return (n);
			}
		}
	}
	argv = replace_aliases(argv);
	n = run_args(argv, front, exe_ret);
	return (n);
}

/**
 * run_args - execute commands with argument
 * @argv: argument vector
 * @front: double pointer
 * @exe_ret: return value of parent process
 *
 * Return: return value of the previous command
 */
int run_args(char **argv, char **front, int *exe_ret)
{
	int n, o;
	int (*builtin)(char **argv, char **front);

	builtin = get_builtin(argv[0]);

	if (builtin)
	{
		n = builtin(argv + 1, front);
		if (n != EXIT)
			*exe_ret = n;
	}
	else
	{
		*exe_ret = execute(argv, front);
		n  = *exe_ret;
	}

	hist++;

	for (o = 0; argv[o]; o++)
		free(argv[o]);

	return (n);
}

/**
 * handle_args - handles arguments
 * @exe_ret: the return value of parent process
 *
 * Return: -2 at EOF
 */
int handle_args(int *exe_ret)
{
	int n = 0, index;
	char **argv, *line = NULL, **front;

	line = get_args(line, exe_ret);
	if (!line)
		return (END_OF_FILE);

	argv = _strtok(line, " ");
	free(line);
	if (!argv)
		return (n);
	if (check_args(argv) != 0)
	{
		*exe_ret = 2;
		free_command(argv, argv);
		return (*exe_ret);
	}
	front = argv;

	for (index = 0; argv[index]; index++)
	{
		if (_strncmp(argv[index], ";", 1) == 0)
		{
			free(argv[index]);
			argv[index] = NULL;
			n = call_args(argv, front, exe_ret);
			argv = &argv[++index];
			index = 0;
		}
	}
	if (argv)
		n = call_args(argv, front, exe_ret);

	free(front);
	return (n);
}

/**
 * check_args - checks for operators
 * @argv: pointer
 *
 * Return: 2 operator is at invalid position
 * or  0 On sucess
 */
int check_args(char **argv)
{
	size_t o;
	char *old, *new;

	for (o = 0; argv[o]; o++)
	{
		old = argv[o];
		if (old[0] == ';' || old[0] == '&' || old[0] == '|')
		{
			if (o == 0 || old[1] == ';')
				return (create_error(&argv[o], 2));
			new = argv[o + 1];
			if (new && (new[0] == ';' || new[0] == '&' || new[0] == '|'))
				return (create_error(&argv[o + 1], 2));
		}
	}
	return (0);
}
