#include "prototypes.h"

/**
 * _strchr - locates a character in a string
 * @s: string
 * @c: character
 * Return: a pointer to the first occurence of c
 * Otherwise NULL
 */
char *_strchr(char *s, char c)
{
	int index;

	for (index = 0; s[index]; index++)
	{
		if (s[index] == c)
			return (s + index);
	}

	return (NULL);
}

/**
 * _strspn - gets the length of a prefix substring
 * @s: string
 * @accept: prefix
 * Return: number of bytes
 */
int _strspn(char *s, char *accept)
{
	int bytes = 0;
	int index;

	while (*s)
	{
		for (index = 0; accept[index]; index++)
		{
			if (*s == accept[index])
			{
				bytes++;
				break;
			}
		}
		s++;
	}
	return (bytes);
}

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 * Return: positive if s1 > s2, 0 if s1 = s2
 * negative if s1 < s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 != *s2)
		return (*s1 - *s2);

	return (0);
}

/**
 * _strncmp - compare two strings
 * @s1: first string
 * @s2: second string
 * @n: first n bytes of the strings to to be compared
 * Return: less than 0 if s1 is shorter than s2,
 * greater than 0 is s1 is longer than s2 and 0 if they match
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t m;

	for (m = 0; s1[m] && s2[m] && m < n; m++)
	{
		if (s1[m] > s2[m])
			return (s1[m] - s2[m]);
		else if (s1[m] < s2[m])
			return (s1[m] - s2[m]);
	}
	if (m == n)
		return (0);
	else
		return (-15);
}
