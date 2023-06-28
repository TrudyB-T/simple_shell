#include "prototypes.h"
/**
 * get_location - finds command path
 * @command: command
 *
 * Return: pathname
 */
char *get_location(char *command)
{
	char **path, *temporal;
	list_t *dirs, *head;
	struct stat st;

	path = _getenv("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs = get_path_dir(*path + 5);
	head = dirs;

	while (dirs)
	{
		temporal = malloc(_strlen(dirs->dir) + _strlen(command) + 2);
		if (!temporal)
			return (NULL);

		_strcpy(temporal, dirs->dir);
		_strcat(temporal, "/");
		_strcat(temporal, command);

		if (stat(temporal, &st) == 0)
		{
			free_list(head);
			return (temporal);
		}

		dirs = dirs->next;
		free(temporal);
	}

	free_list(head);

	return (NULL);
}

/**
 * fill_path_dir - copies path
 * @path: path
 * 
 * Return: path copy
 */
char *fill_path_dir(char *path)
{
	int x, length = 0;
	char *path_copy, *pwd;

	pwd = *(_getenv("PWD")) + 4;
	for (x = 0; path[x]; x++)
	{
		if (path[x] == ':')
		{
			if (path[x + 1] == ':' || x == 0 || path[x + 1] == '\0')
				length = length + _strlen(pwd) + 1;
			else
				length = length + 1;
		}
		else
			length = length + 1;
	}
	path_copy = malloc(sizeof(char) * (length + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';
	for (x = 0; path[x]; x++)
	{
		if (path[x] == ':')
		{
			if (x == 0)
			{
				_strcat(path_copy, pwd);
				_strcat(path_copy, ":");
			}
			else if (path[x + 1] == ':' || path[x + 1] == '\0')
			{
				_strcat(path_copy, ":");
				_strcat(path_copy, pwd);
			}
			else
				_strcat(path_copy, ":");
		}
		else
		{
			_strncat(path_copy, &path[x], 1);
		}
	}
	return (path_copy);
}

/**
 * get_path_dir - splits string into tokens
 * @path: path
 *
 * Return: pointer to linked list
 */
list_t *get_path_dir(char *path)
{
	int marks;
	char **dirs, *path_copy;
	list_t *head = NULL;

	path_copy = fill_path_dir(path);
	if (!path_copy)
		return (NULL);
	dirs = _strtok(path_copy, ":");
	free(path_copy);
	if (!dirs)
		return (NULL);

	for (marks = 0; dirs[marks]; marks++)
	{
		if (add_node_end(&head, dirs[marks]) == NULL)
		{
			free_list(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (head);
}
