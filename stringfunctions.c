#include "prototypes.h"

/**
 * _strlen - returns the length of a string
 * @s: the string to be used
 * Return: length of the string
 */
int _strlen(const char *s)
{
	int len = 0, a;

	for (a = 0; s[a] != '\0'; a++)
	{
		len++;
	}
	return (len);
}

/**
 * *_strcpy - copies the string pointedto by src
 * @dest: buffer pointed to by dest
 * @src: string pointed to by src
 * Return: the pointer to dest
 */
char *_strcpy(char *dest, const char *src)
{
	char *s = dest;
	int i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = ('\0');
	return (s);
}

/**
 * _strcat - function that concantenates two strings
 * @dest: a pointer to destination string
 * @src: a pointer to source string
 *
 * Return: pointer to destination string
 */
char *_strcat(char *dest, const char *src)
{
	char *destTemp;
	const char *srcTemp;

	destTemp = dest;
	srcTemp =  src;

	while (*destTemp != '\0')
		destTemp++;

	while (*srcTemp != '\0')
		*destTemp++ = *srcTemp++;
	*destTemp = '\0';
	return (dest);
}

/**
 * _strncat - function that concantenates two strings
 * @dest: a pointer to the destination string
 * @src: a pointer to the source string
 * @n: number of bytes to copy from src
 * Return: pointer to destination string
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len = _strlen(dest);
	size_t m;

	for (m = 0; m < n && src[m] != '\0'; m++)
		dest[dest_len + m] = src[m];
	dest[dest_len + m] = '\0';

	return (dest);
}
