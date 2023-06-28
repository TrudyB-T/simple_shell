#include "prototypes.h"

/**
 * token_len - splits strings
 * index marking the end of the first token
 * @str: string
 * @delim: delimiter
 * Return: index
 */
int token_len(char *str, char *delim)
{
	int index = 0, length = 0;

	while (*(str + index) && *(str + index) != *delim)
	{
		length = length + 1;
		index = index + 1;
	}

	return (length);
}

/**
 * count_tok - counts the number of delimited word
 * @str: string
 * @delim: delimiter
 * Return: total word count within str
 */
int count_tok(char *str, char *delim)
{
	int index, tokens = 0, length = 0;

	for (index = 0; *(str + index); index++)
		length = length + 1;

	for (index = 0; index < length; index++)
	{
		if (*(str + index) != *delim)
		{
			tokens = tokens + 1;
			index = index + token_len(str + index, delim);
		}
	}

	return (tokens);
}

/**
 * _strtok - this function tokenizes a string
 * @line: concerned string
 * @delim: delimiter
 * Return: pointer to array with tokenized words
 */
char **_strtok(char *line, char *delim)
{
	char **ptr;
	int index = 0, tokens, x, characters, y;

	tokens = count_tok(line, delim);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (x = 0; x < tokens; x++)
	{
		while (line[index] == *delim)
			index = index + 1;

		characters = token_len(line + index, delim);

		ptr[x] = malloc(sizeof(char) * (characters + 1));
		if (!ptr[x])
		{
			for (index -= 1; index >= 0; index--)
				free(ptr[index]);
			free(ptr);
			return (NULL);
		}

		for (y = 0; y < characters; y++)
		{
			ptr[x][y] = line[index];
			index++;
		}

		ptr[x][y] = '\0';
	}
	ptr[x] = NULL;
	ptr[x + 1] = NULL;

	return (ptr);
}
