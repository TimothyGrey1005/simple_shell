#include "shell.h"

/**
 * _strlen - a funct to return a string len
 * @s: str
 * Return: reslt.
 */

int _strlen(char *s)
{
	int f = 0;

	if (!s)
	{
		return (0);
	}

	while (*s++)
	{
		f++;
	}

	return (f);
}

/**
 * _strcmp - a func to compare two strs.
 * @str1: 1st str
 * @str2: 2nd str
 * Return: result
 */

int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
		{
			return (*str1 - *str2);
		}
		str1++;
		str2++;
	}
	if (*str1 == *str2)
	{
		return (0);
	}
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_with - a func to checks
 * @stack: search str
 * @ndle: sub str
 * Return: result
 */

char *starts_with(const char *stack, const char *ndle)
{
	while (*ndle)
		if (*ndle++ != *stack++)
		{
			return (NULL);
		}
	return ((char *)stack);
}

/**
 * _strcat - a func to mixes two strs
 * @destination: dest buff
 * @source: src buff
 * Return: results
 */
char *_strcat(char *destination, char *source)
{
	char *result = destination;

	while (*destination)
	{
		destination++;
	}
	while (*source)
	{
		*destination++ = *source++;
	}
	*destination = *source;
	return (result);
}
