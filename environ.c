#include "prototypes.h"

/**
 * ___env - prints environment
 * @args: Argument vector
 * @front: pointer 
 *
 * Return: -1 on error and 0 on sucess.
 */
int __env(char **args, char __attribute__((__unused__)) **front)
{
	int mark;
	char newLine = '\n';

	if (!environ)
		return (-1);

	for (mark = 0; environ[mark]; mark++)
	{
		write(STDOUT_FILENO, environ[mark], _strlen(environ[mark]));
		write(STDOUT_FILENO, &newLine, 1);
	}

	(void)args;
	return (0);
}

/**
 * __setenv - sets environment variables
 * @args: Argument vector
 * @front: pointer
 *
 * Return: -1 on error and 0 on sucess.
 */
int __setenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var = NULL, **updated_environ, *updated_value;
	size_t size;
	int mark;

	if (!args[0] || !args[1])
		return (create_error(args, -1));

	updated_value = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!updated_value)
		return (create_error(args, -1));
	_strcpy(updated_value, args[0]);
	_strcat(updated_value, "=");
	_strcat(updated_value, args[1]);

	env_var = _getenv(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = updated_value;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	updated_environ = malloc(sizeof(char *) * (size + 2));
	if (!updated_environ)
	{
		free(updated_value);
		return (create_error(args, -1));
	}

	for (mark = 0; environ[mark]; mark++)
		updated_environ[mark] = environ[mark];

	free(environ);
	environ = updated_environ;
	environ[mark] = updated_value;
	environ[mark + 1] = NULL;

	return (0);
}

/**
 * __unsetenv - deletes environment variables
 * @args: Argument vector
 * @front: pointer
 *
 * Return: -1 on error and 0 on sucess.
 */
int __unsetenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var, **updated_environ;
	size_t size;
	int mark, mark2;

	if (!args[0])
		return (create_error(args, -1));
	env_var = _getenv(args[0]);
	if (!env_var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	updated_environ = malloc(sizeof(char *) * size);
	if (!updated_environ)
		return (create_error(args, -1));

	for (mark = 0, mark2 = 0; environ[mark]; mark++)
	{
		if (*env_var == environ[mark])
		{
			free(*env_var);
			continue;
		}
		updated_environ[mark] = environ[mark];
		mark2 = mark2 + 1;
	}
	free(environ);
	environ = updated_environ;
	environ[size - 1] = NULL;

	return (0);
}
