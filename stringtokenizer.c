#include "prototypes.h"

/**
 * tokenize - breaks strings into tokens
 * @ptr: pointer to string
 * @bufsize: buffer size to allocate
 *
 * Return: nothing
 */


char **tokenize(char *ptr, int bufsize)
{
	int k = 0, tok_len;
	char *end_tok, **argv;


	argv = malloc(sizeof(char *) * bufsize);

	if (argv == NULL)
	{
		perror("./hsh");
		free(argv);
		exit(0);	
	}
	while (*ptr != '\0')
	{
		while (*ptr == ' ')
			ptr++;
		if (*ptr == '\0')
			break;
		end_tok = ptr;
		while(*end_tok != '\0' && *end_tok != ' ')
			end_tok++;
		tok_len = end_tok - ptr;
		argv[k] = malloc(tok_len + 1);
		if (argv[k] == NULL)
		{
			perror("./hsh");
			exit(0);
		}
		_strncpy(argv[k], ptr, tok_len);
		argv[k][tok_len] = '\0';
		ptr = end_tok;
		k++;

		if (k >= bufsize)
		{
			bufsize += BUFFER_LEN;
			argv = reallocate(argv, sizeof(argv), sizeof(char *) * bufsize);
			if (argv == NULL)
			{
				perror("./hsh");
				exit(0);
			}
		}
	}

	argv[k] = NULL;

	return (argv);
}


/**
 * *_strncpy - copies a string
 * @dest: string destination
 * @src: string source
 * @n: number of bytes
 * Return: pointer to the resulting dest
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; (i < n && src[i] != '\0'); i++)
	{
		dest[i] = src[i];
	}
	for (; i < n; i++)
	{
		dest[i] = '\0';
	}
	return (dest);
}
