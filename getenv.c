 #include "shell.h"

/**
 * get_environ - it will return the copy of the string array of environment
 * @info: A structure which contains the potential arguments.
*It is used to manage a constant prototype function.
 * Return: A 0 value is always returned
*/
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - It removes an environment variable
 * @info: A structure which contains the potential arguments.
*It is used to manage a constant prototype function.
 *  Return: Returns a 1 on delete, 0 if output is otherwise
 * @var: the string env var property
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->string, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - A new environment variable is to be initialized,
 *             or an already existing one is modified
 * @info: A structure which contains the potential arguments.
*It is used to manage a constant prototype function.
 * @var: declares the str environment variable property
 * @value: the value of the str environment variable
 *  Return: A 0 value is always returned
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->string, var);
		if (p && *p == '=')
		{
			free(node->string);
			node->string = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
