#include "prototypes.h"

/**
 * get_lineptr - reassigns the lineptr
 * @lineptr: a pointer to an array of strings
 * @s: size of lineptr
 * @buffer: a buffer to store temporal strings
 * @c: size of buffer
 */
void get_lineptr(char **lineptr, size_t *s, char *buffer, size_t c)
{
	if (!lineptr)
	{
		if (c > 100)
		{
			*s = c;
		}
		else
		{
			*s = 100;
		}
		*lineptr = buffer;
	}
	else if (*s < c)
	{
		if (c > 100)
		{
			*s = c;
		}
		else
		{
			*s = 100;
		}
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}


	

/**
 * _getline - gets the input string from user
 * @lineptr: input string
 * @s: size of lineptr
 * @stream: stream to read
 * Return: number of bytes
 */
ssize_t _getline(char **lineptr, size_t *s, FILE *stream)
{
	ssize_t num;
	char b = 'x', *buffer;
	int n;
	static ssize_t rec;

	if (!rec)
		fflush(stream);
	else
		return (-1);
	rec = 0;
	buffer = malloc(sizeof(char) * 100);
	if (buffer == NULL)
		return (-1);
	while (b != '\n')
	{
		n = read(STDIN_FILENO, &b, 1);
		if (n == -1 || (n == 0 && rec == 0))
		{
			free(buffer);
			return(-1);
		}
		if (n == 0 && rec != 0)
		{
			rec++;
			break;
		}
		if (rec >= 100)
			buffer = reallocate(buffer, rec, rec + 1);
		buffer[rec] = b;
		rec++;
	}
	buffer[rec] = '\0';

	get_lineptr(lineptr, s, buffer, rec);

	num = rec;
	if (n != 0)
		rec = 0;
	return (num);
}

