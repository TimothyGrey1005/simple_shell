 #include "shell.h"

/**
 * _eputs - A string input is printed
 * @str: the string input that is to be printed
 *
 * Return: No output is returned
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - The character of variable c is written to stderr
 * @c: The character of variable c is to be printed
 *
 * Return: A value of 1 is returned on successful execution
 * -1 is returned on error execution,
 * and the error number is appropriately set.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - The character of variable c is written to fd provided
* @c: The character of variable c is to be printed
* @fd: The descriptor of file to be written to
 *
*Return: A value of 1 is returned on successful execution,
*-1 is returned on error execution,
*and the error number is appropriately set.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putsfd - An input string is printed
 * @str: the string input that is to be printed
 * @fd: The descriptor of file to be written to
 *
 * Return: the number of characters printed out
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
