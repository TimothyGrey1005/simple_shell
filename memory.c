#include "shell.h"

/**
 * bfree - a function to free a pointer
 * @ptr: pointer to the address
 * Return: results
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
