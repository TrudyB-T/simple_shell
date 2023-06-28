#include "prototypes.h"

/**
 * _copyenv - copies environment
 *
 * Return: NULL on error
 */
char **_copyenv(void)
{
	char **new_environ;
	size_t size;
	int index;

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
		return (NULL);

	for (index = 0; environ[index]; index++)
	{
		new_environ[index] = malloc(_strlen(environ[index]) + 1);

		if (!new_environ[index])
		{
			for (index--; index >= 0; index--)
				free(new_environ[index]);
			free(new_environ);
			return (NULL);
		}
		_strcpy(new_environ[index], environ[index]);
	}
	new_environ[index] = NULL;

	return (new_environ);
}

/**
 * free_env - frees malloc for env
 *
 *
 */
void free_env(void)
{
	int index;

	for (index = 0; environ[index]; index++)
		free(environ[index]);
	free(environ);
}

/**
 * _getenv - gets environment variables
 * @var: variable
 *
 * Return: NULL if var is empty
 */
char **_getenv(const char *var)
{
	int index, length;

	length = _strlen(var);
	for (index = 0; environ[index]; index++)
	{
		if (_strncmp(var, environ[index], length) == 0)
			return (&environ[index]);
	}

	return (NULL);
}
