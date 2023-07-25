#include "shell.h"

/**
 * bfree - frees a ptr
 * @ptr: addres
 * Return: results.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
