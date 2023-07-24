#include "shell.h"

/**
 * _strcpy - a function that copies a str
 * @destination: destination address
 * @source: src
 * Return: results
 */

char *_strcpy(char *destination, char *source)
{
	int c = 0;

	if (destination == source || source == 0)
	{
		return (destination);
	}
	while (source[c])
	{
		destination[c] = source[c];
		c++;
	}

	destination[c] = 0;
	return (destination);

}
/**
 * _strdup - a function that duplicates a string
 * @str: string
 * Return: results
 */

char *_strdup(const char *str)
{
	int len = 0;
	char *retn;

	if (str == NULL)
	{
		return (NULL);
	}
	while (*str++)
	{
		len++;
	}
	retn = malloc(sizeof(char) * (len + 1));

	if (!retn)
	{
		return (NULL);
	}

	for (len++; len--;)
	{
		retn[len] = *--str;
	}
	return (retn);
}

/**
 * _puts - a funtion that print a string
 * @str: printed string
 * Return: void
 */
void _puts(char *str)
{
	int s = 0;

	if (!str)
	{
		return;
	}

	while (str[s] != '\0')
	{
		_putchar(str[s]);
		s++;
	}
}

/**
 * _putchar -print the char to stdout
 * @ch: print char
 * Return: results.
 */
int _putchar(char ch)
{
	static int s;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || s >= WRITE_BUF_SIZE)
	{
		write(1, buf, s);
		s = 0;
	}

	if (ch != BUF_FLUSH)
	{
		buf[s++] = ch;
	}
	return (1);
}
