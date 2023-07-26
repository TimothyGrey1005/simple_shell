#include "shell.h"

/**
 * bfree - frees a pointer
 * @ptr: pointer to the address to be freed
 * Return: 1 if successful, 0 otherwise.
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
