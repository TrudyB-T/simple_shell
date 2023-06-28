#include "prototypes.h"

/**
 * get_builtin - gets the builtin command input
 * 
 * @command: command
 * Return: builtin command.
 */
int (*get_builtin(char *command))(char **args, char **front)
{
	builtin_t funcs[] = {
		{ "exit", __exit },
		{ "env", __env },
		{ "setenv", __setenv },
		{ "unsetenv", __unsetenv },
		{ "cd", __cd },
		{ "alias",__alias },
		{ "help", __help },
		{ NULL, NULL }
	};
	int s1;

	for (s1 = 0; funcs[s1].name; s1++)
	{
		if (_strcmp(funcs[s1].name, command) == 0)
			break;
	}
	return (funcs[s1].f);
}

/**
 * exit - leave program
 * @args: argument vector
 * @front: pointer to  args.
 * Return: -3 if there is no argument.
 *         
 * 
 */
int __exit(char **args, char **front)
{
	int s1, length = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			s1 = 1;
			length = length + 1;
		}
		for (; args[0][s1]; s1++)
		{
			if (s1 <= length && args[0][s1] >= '0' && args[0][s1] <= '9')
				num = (num * 10) + (args[0][s1] - '0');
			else
				return (create_error(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (create_error(--args, 2));
	args -= 1;
	free_command(args, front);
	free_env();
	free_alias_list(aliases);
	exit(num);
}

/**
 * cd - changes directories
 * @args: argument vector
 * @front: pointer to args.
 * Return: - 2 if directory is not found
 *         
 */
int __cd(char **args, char __attribute__((__unused__)) **front)
{
	char **dir_info, *new_line = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
					(chdir(*_getenv("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (create_error(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(oldpwd);
				return (create_error(args, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			chdir(*(_getenv("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "OLDPWD";
	dir_info[1] = oldpwd;
	if (__setenv(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (__setenv(dir_info, dir_info) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(oldpwd);
	free(pwd);
	free(dir_info);
	return (0);
}

/**
 * help -  help function
 * @front: pointer to args.
 * Return:  -1 on failure and 0 on sucess.
 *       
 */
int __help(char **args, char __attribute__((__unused__)) **front)
{
	if (!args[0])
		help_all();
	else if (_strcmp(args[0], "alias") == 0)
		help_alias();
	else if (_strcmp(args[0], "cd") == 0)
		help_cd();
	else if (_strcmp(args[0], "exit") == 0)
		help_exit();
	else if (_strcmp(args[0], "env") == 0)
		help_env();
	else if (_strcmp(args[0], "setenv") == 0)
		help_setenv();
	else if (_strcmp(args[0], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(args[ 0], "help") == 0)
		help_help();
	else
		write(STDERR_FILENO, name, _strlen(name));

	return (0);
}
