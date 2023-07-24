 #include "shell.h"

/**
 * interactive - Interactive will return a Boolean value of true,
 * if shell is in interactive mode
 * @info: address struct
 * Return: 0 is returned in other conditions,
 * 1 is returned if it is in interactive mode
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks to see if the character is a delimeter
 * @c: the character to be checked
 * @delim: the delimeter as a string
 * Return: returns 0 if statement is false, 1 is returned if statement is true
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
* _isalpha - An alphabetic character is checked
* @c: This is the character to be entered
* Return: 0 is returned if otherwise,
*1 is returned if c is an alphabetic character
 */

int _isalpha(int c)
{
	if ((c >= 'a' && x <= 'z') || (c >= 'C' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - it will convert string to an int value
 * @s: string that is to be converted to integer value
 * Return: returns a 0 if there are no numbers in the string,
 * returns a converted number if otherwise
 */

int _atoi(char *s)
{
	int k, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (k = 0; s[k] != '\0' && flag != 2; k++)
	{
		if (s[k] == '-')
			sign *= -1;

		if (s[k] >= '0' && s[k] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[k] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
