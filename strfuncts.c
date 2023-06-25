#include "prototypes.h"

/**
 * _strlen - returns the length of a string
 * @s: the string to be used
 * Return: 0
 */
int _strlen(char *s)
{
	int len = 0, a;

	for (a = 0; s[a] != '\0'; a++)
	{
		len++;
	}
	return (len);
}

/**
 * *_strconcat - concatenates two strings
 * @s1: string 1
 * @s2: string 2
 * Return: a pointer to the new string s1 followed by s2
 * Otherwise, NULL means fail.
 */
char *_strconcat(char *s1, char *s2)
{
	unsigned int i, j, l1, l2;
	char *New;

	if (s1 == NULL)
		s1 = ("");
	if (s2 == NULL)
		s2 = ("");

	l1 = 0, l2 = 0;

	while (s1 && s1[l1])
	{
		l1++;
	}
	while (s2 && s2[l2])
	{
		l2++;
	}
	New = malloc(sizeof(char) * (l1 + l2 + 1));

	if (New == NULL)
	{
		return (NULL);
	}
	for (i = 0; i < l1; i++)
	{
		New[i] = s1[i];
	}
	for (j = 0; j < l2; j++)
	{
		New[i++] = s2[j];
	}
	New[i] = '\0';

	return (New);
}



/**
 * _atoi - converts string to integer
 * @s : pointer to be converted
 * Return: integer or 0 if
 * there are no numbers in the string
 */

int _atoi(char *s)
{
	int k = 0;
	unsigned int l = 0;
	int j = 0;
	int m = 1;

	while (s[k])
	{
		if (s[k] == 45)
		{
			m *= -1;
		}
		while (s[k] >= 48 && s[k] <= 57)
		{
			j = 1;
			l = (l * 10) + (s[k] - '0');
			k++;
		}
		if (j == 1)
		{
			break;
		}
		k++;
	}
	l *= m;
	return (l);
}



/**
 *  _strcmp - compares two strings
 *
 * @s1 :the pointer to the first string to be compared
 *
 * @s2 :the pointer to the second string to be compared
 *
 * Return: the difference between *s1 and *s2
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
