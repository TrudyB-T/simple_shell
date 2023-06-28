#include "prototypes.h"

/**
 * __alias - creates alias
 * @argv: argument vctor
 * @font: ouble pointer to argv
 * Return: -1 on failure, 0 on sucess
 */


int __alias(char **argv, char __attribute__((__unused__)) **front)
{
	alias_t *u = aliases;
	int z;
	int s = 0;
	char *index;

	if (!argv[0])
	{
		while (u)
		{
			print_alias(u);
			u = u->next;
		}
		return (s);
	}
	for (z = 0; argv[z]; z++)
	{
		u = aliases;
		index = _strchr(argv[z], '=');
		if (!index)
		{
			while (u)
			{
				if (_strcmp(argv[z], u->name) == 0)
				{
					print_alias(u);
					break;
				}
				u = u->next;
			}
			if (!u)
				s = create_error(argv + z, 1);
		}
		else
			set_alias(argv[z], index);
	}
	return (s);
}

/**
 * set_alias - sets alias
 * @va_name: variable name
 * @value: alias value
 */
void set_alias(char *var_name, char *value)
{
	alias_t *u = aliases;
	int len, q, r;
	char *new_index;

	*value = '\0';
	value = value + 1;
	len = _strlen(value) - _strspn(value, "'\"");
	new_index = malloc(sizeof(char) * (len + 1));
	if (!new_index)
		return;
	for (q = 0, r = 0; value[q]; q++)
	{
		if (value[q] != '\'' && value[q] != '"')
			new_index[r++] = value[q];
	}
	new_index[r] = '\0';
	while (u)
	{
		if (_strcmp(var_name, u->name) == 0)
		{
			free(u->value);
			u->value = new_index;
			break;
		}
		u = u->next;
	}
	if (!u)
		_alias_end(&aliases, var_name, new_index);
}

/**
 * print_alias - prints alias
 * @alias: pointer
 *
 * Return: -1 on error and 0 on sucess.
 */
void print_alias(alias_t *alias)
{
	char *str;
	int len = _strlen(alias->name) + _strlen(alias->value) + 4;

	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return;
	_strcpy(str, alias->name);
	_strcat(str, "='");
	_strcat(str, alias->value);
	_strcat(str, "'\n");

	write(STDOUT_FILENO, str, len);
	free(str);
}
/**
 * replace_aliases - replaces aliases
 * @argv: argument vector
 *
 * Return: pointer to argv
 */
char **replace_aliases(char **argv)
{
	alias_t *u;
	int z;
	char *new_index;

	if (_strcmp(argv[0], "alias") == 0)
		return (argv);
	for (z = 0; argv[z]; z++)
	{
		u = aliases;
		while (u)
		{
			if (_strcmp(argv[z], u->name) == 0)
			{
				new_index = malloc(sizeof(char) * (_strlen(u->value) + 1));
				if (!new_index)
				{
					free_command(argv, argv);
					return (NULL);
				}
				_strcpy(new_index, u->value);
				free(argv[z]);
				argv[z] = new_index;
				z = z - 1;
				break;
			}
			u = u->next;
		}
	}

	return (argv);
}
