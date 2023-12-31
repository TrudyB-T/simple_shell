#include "prototypes.h"

/**
 * handle_line - splits lines read from stdin
 * @line: string to be used
 * @read: length in bytes
 */
void handle_line(char **line, ssize_t read)
{
	char *old_line, *new_line,previous, current, next;
	size_t m, j;
	ssize_t new_len;

	new_len = _new_len(*line);
	if (new_len == read - 1)
		return;
	new_line = malloc(new_len + 1);
	if (!new_line)
		return;
	j = 0;
	old_line = *line;
	for (m = 0; old_line[m]; m++)
	{
		current = old_line[m];
		next = old_line[m + 1];
		if (m != 0)
		{
			previous = old_line[m - 1];
			if (current == ';')
			{
				if (next == ';' && previous != ' ' && previous != ';')
				{
					new_line[j++] = ' ';
					new_line[j++] = ';';
					continue;
				}
				else if (previous == ';' && next != ' ')
				{
					new_line[j++] = ';';
					new_line[j++] = ' ';
					continue;
				}
				if (previous != ' ')
					new_line[j++] = ' ';
				new_line[j++] = ';';
				if (next != ' ')
					new_line[j++] = ' ';
				continue;
			}
			else if (current == '&')
			{
				if (next == '&' && previous != ' ')
					new_line[j++] = ' ';
				else if (previous == '&' && next != ' ')
				{
					new_line[j++] = '&';
					new_line[j++] = ' ';
					continue;
				}
			}
			else if (current == '|')
			{
				if (next == '|' && previous != ' ')
					new_line[j++]  = ' ';
				else if (previous == '|' && next != ' ')
				{
					new_line[j++] = '|';
					new_line[j++] = ' ';
					continue;
				}
			}
		}
		else if (current == ';')
		{
			if (m != 0 && old_line[m - 1] != ' ')
				new_line[j++] = ' ';
			new_line[j++] = ';';
			if (next != ' ' && next != ';')
				new_line[j++] = ' ';
			continue;
		}
		new_line[j++] = old_line[m];
	}
	new_line[j] = '\0';

	free(*line);
	*line = new_line;
}

/**
 * _new_len - gets the length line split
 * @line: line to check
 * Return: new length of the line
 * Description: Cuts short lines containing
 * '#' comments with '\0'.
 */
ssize_t _new_len(char *line)
{
	size_t m;
	ssize_t new_len = 0;
	char current, next;

	for (m = 0; line[m]; m++)
	{
		current = line[m];
		next = line[m + 1];
		if (current == '#')
		{
			if (m == 0 || line[m - 1] == ' ')
			{
				line[m] = '\0';
				break;
			}
		}
		else if (m != 0)
		{
			if (current == ';')
			{
				if (next == ';' && line[m - 1] != ' ' && line[m - 1] != ';')
				{
					new_len += 2;
					continue;
				}
				else if (line[m - 1] == ';' && next != ' ')
				{
					new_len += 2;
					continue;
				}
				if (line[m - 1] != ' ')
					new_len++;
				if (next != ' ')
					new_len++;
			}
			else
				logical_ops(&line[m], &new_len);
		}
		else if (current == ';')
		{
			if (m != 0 && line[m - 1] != ' ')
				new_len++;
			if (next != ' ' && next != ';')
				new_len++;
		}
		new_len++;
	}
	return (new_len);
}
/**
 * logical_ops - Checks a line for logical operators "||" or "&&".
 * @line: A pointer to the character to check in the line.
 * @new_len: Pointer to new_len in get_new_len function.
 */
void logical_ops(char *line, ssize_t *new_len)
{
	char previous, current, next;

	previous = *(line - 1);
	current = *line;
	next = *(line + 1);

	if (current == '&')
	{
		if (next == '&' && previous != ' ')
			(*new_len)++;
		else if (previous == '&' && next != ' ')
			(*new_len)++;
	}
	else if (current == '|')
	{
		if (next == '|' && previous != ' ')
			(*new_len)++;
		else if (previous == '|' && next != ' ')
			(*new_len)++;
	}
}
