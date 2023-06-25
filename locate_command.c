#include "prototypes.h"

/**
 * locate_command - search for commands specified by PATH variables
 * @argv: the command to search
 *
 * Return: a pointer to the path of the command
 */
char *locate_command(char *argv)
{
	char *path = NULL, *tok = NULL, *path_copy = NULL;
	int j = 0, l = 0;
	struct stat fileinfo;

	path = _searchenv("PATH");

	for (l = 0; path[l]; l++)
		;
	path_copy = malloc(sizeof(char) * l + 1);

	for (j = 0; path[j]; j++)
		path_copy[j] = path[j];
	path_copy[j] = '\0';

	tok = strtok(path_copy, ":");
	tok = _strconcat(tok, "/");
	tok = _strconcat(tok, argv);

	while (tok)
	{
		if (stat(tok, &fileinfo) == 0)
			return (tok);
		tok = strtok(NULL, ":");
		if (tok)
		{
			tok = _strconcat(tok, "/");
			tok = _strconcat(tok, argv);
		}
	}
	free(tok);
	free(path_copy);
	return (NULL);
}
