#include "prototypes.h"
/**
 * free_command - frees command arguments
 * @argv: the argument to be freed
 * @front: buffer
 */
void free_command(char **argv, char **front)
{
	size_t i;

	for (i = 0; argv[i] || argv[i + 1]; i++)
		free(argv[i]);

	free(front);
}

/**
 * get_pid - gets the current process ID
 * Return: current process ID
 * Otherwise NULL
 */
char *get_pid(void)
{
	size_t i = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[i] != ' ')
		i++;
	buffer[i] = '\0';

	close(file);
	return (buffer);
}

/**
 *  _searchenv - searches for the value of an environmental variable.
 * @begin: env  variable to search for.
 * @len: length of the varible
 *
 * Return: the value of the env variable
 * Otherwise an empty string
 */
char *_searchenv(char *begin, int len)
{
	char **address;
	char *replace = NULL, *temp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, begin, len);

	address = _getenv(var);
	free(var);
	if (address)
	{
		temp = *address;
		while (*temp != '=')
			temp++;
		temp++;
		replace = malloc(_strlen(temp) + 1);
		if (replace)
			_strcpy(replace, temp);
	}

	return (replace);
}

/**
 * replace_var - handles variable replacement.
 * @line: double pointer containing the command
 * and arguments.
 * @exe_ret: pointer to the return value of the last
 * executed command.
 */
void replace_var(char **line, int *exe_ret)
{
	int j, k = 0, len;
	char *replace = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (j = 0; old_line[j]; j++)
	{
		if (old_line[j] == '$' && old_line[j + 1] &&
				old_line[j + 1] != ' ')
		{
			if (old_line[j + 1] == '$')
			{
				replace = get_pid();
				k = j + 2;
			}
			else if (old_line[j + 1] == '?')
			{
				replace = _itoa(*exe_ret);
				k = j + 2;
			}
			else if (old_line[j + 1])
			{
				for (k = j + 1; old_line[k] &&
						old_line[k] != '$' &&
						old_line[k] != ' '; k++)
					;
				len = k - (j + 1);
				replace = _searchenv(&old_line[j + 1], len);
			}
			new_line = malloc(j + _strlen(replace)
					  + _strlen(&old_line[k]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			_strncat(new_line, old_line, j);
			if (replace)
			{
				_strcat(new_line, replace);
				free(replace);
				replace = NULL;
			}
			_strcat(new_line, &old_line[k]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			j = -1;
		}
	}
}
