#include "prototypes.h"

/**
 * reallocate - reallocates memory
 * @str: pointer to old memory
 * @size1: size of old memory
 * @size2: size of new meory allocation
 *
 * Return: NULL if memory allocation fails or pointer to memory on sucess
 */


void *reallocate(void *str, unsigned int size1, unsigned int size2)
{
	char *ptr;
	unsigned int n, max = size2;
	char *ptr1 = str;

	if (str == NULL)
	{
		ptr = malloc(size2);

		return (ptr);
	}

	else if (size2 == 0)
	{
		free(str);
		return (NULL);
	}

	else if (size2 == size1)
		return (str);

	ptr = malloc(size2);

	if (ptr == NULL)
		return (NULL);

	if (size2 > size1)
		max = size1;

	for (n = 0; n < max; n++)

		ptr[n] = ptr1[n];
	free(str);
	return (ptr);
}

