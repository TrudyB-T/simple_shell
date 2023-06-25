#include "prototypes.h"

/**
 * _printenv - prints environment variable
 *
 * Return: nothing
 */
void _printenv(void)
{
	char *env = *environ;
	int len1, len2;

	for (len1 = 1; env != NULL; len1++)
	{
		len2 = 0;
		while (env[len2])
		{
			write(1, &env[len2], 1);
			len2++;
		}
		write(1, "\n", 1);
		env = environ[len1];
	}
}
