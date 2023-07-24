#include "shell.h"

/**
 * _memset -funct to fill mem
 * @s: ptr
 * @b: tbyte b
 * @n: byte amt
 * Return: Results
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int k;

	for (k = 0; k < n; k++)
	{
		s[k] = b;
	}
	return (s);
}

/**
 * ffree - a func to release a str
 * @pp: str
 */

void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
	{
		return;
	}
	while (*pp)
	{
		free(*pp++);
	}
	free(a);
}

/**
 * _realloc - a func to move code
 * @ptr: ptr
 * @old_size: bte size
 * @new_size: byte size
 * Return: ptr
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *j;

	if (!ptr)
	{
		return (malloc(new_size));
	}

	if (!new_size)
	{
		return (free(ptr), NULL);
	}

	if (new_size == old_size)
	{
		return (ptr);
	}

	j = malloc(new_size);

	if (!j)
	{
		return (NULL);
	}

	old_size = old_size < new_size ? old_size : new_size;

	while (old_size--)
	{
		j[old_size] = ((char *)ptr)[old_size];
	}

	free(ptr);
	return (j);
}
