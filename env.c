#include "prototypes.h"

/**
 * _searchenv - finds the environment variable name
 * @env: name of the environment variable
 * Return: a pointer to a value string
 * Otherwise NULL
 */
char *_searchenv(char *env)
{
	char *value = NULL;
	int k = 0, l;

	if (env == NULL)
		return (NULL);

	while (environ[k])
	{
		l = 0;

		while (env[l] && env[l] == environ[k][l])
		{
			l++;
		}
		if (env[l] == '\0')
		{
			value = environ[k] + l + 1;
		}
		k++;
	}
	return (value);
}
