#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * is_chain - a func to checks chain del
 * @info: param
 * @buf: c buffer
 * @p: address
 * Return: results
 */

int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t s = *p;

	if (buf[s] == '|' && buf[s + 1] == '|')
	{
		buf[s] = 0;
		s++;
		info->cmd_buf_type = CMD_OR;
	}

	else if (buf[s] == '&' && buf[s + 1] == '&')
	{
		buf[s] = 0;
		s++;
		info->cmd_buf_type = CMD_AND;
	}

	else if (buf[s] == ';')
	{
		buf[s] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = s;
	return (1);
}

/**
 * check_chain - a func to test chaining
 * @info: param struct
 * @buf: char buff
 * @p: buff pos address
 * @i: start pos
 * @len: buff len
 * Return: none
 */

void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t s = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			s = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			s = len;
		}
	}

	*p = s;
}

/**
 * replace_alias - a function that switches
 * @info: param
 * Return: results
 */

int replace_alias(info_t *info)
{
	int s;
	list_t *node;
	char *c;

	for (s = 0; s < 10; s++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
		{
			return (0);
		}
		free(info->argv[0]);
		c = strchr(node->string, '=');

		if (!c)
		{
			return (0);
		}

		c = _strdup(c + 1);

		if (!c)
		{
			return (0);
		}

		info->argv[0] = c;
	}
	return (1);
}

/**
 * replace_vars - a func to switch variables
 * @info: param
 * Return: return
 */

int replace_vars(info_t *info)
{
	int s = 0;
	list_t *node;

	for (s = 0; info->argv[s]; s++)
	{
		if (info->argv[s][0] != '$' || !info->argv[s][1])
		{
			continue;
		}

		if (!_strcmp(info->argv[s], "$?"))
		{
			replace_string(&(info->argv[s]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}

		if (!_strcmp(info->argv[s], "$$"))
		{
			replace_string(&(info->argv[s]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}

		node = node_starts_with(info->env, &info->argv[s][1], '=');

		if (node)
		{
			replace_string(&(info->argv[s]),
					_strdup(_strchr(node->string, '=') + 1));
			continue;
		}

		replace_string(&info->argv[s], _strdup(""));
	}

	return (0);
}

/**
 * replace_string - a func to check that switches strings
 * @old1: addr
 * @new1: str
 * Return: results
 */
int replace_string(char **old1, char *new1)
{
	free(*old1);
	*old1 = new1;
	return (1);
}
