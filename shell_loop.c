#include "shell.h"

/**
 * hsh - shell loop func
 * @info: param
 * @av: arg vect
 * Return: result
 */

int hsh(info_t *info, char **av)
{
	ssize_t k = 0;
	int builtin_r = 0;

	while (k != -1 && builtin_r != -2)
	{
		clear_info(info);

		if (interactive(info))
			_puts("$ ");

		_eputchar(BUF_FLUSH);
		k = get_input(info);

		if (k != -1)
		{
			set_info(info, av);
			builtin_r = find_builtin(info);

			if (builtin_r == -1)
			{
				find_cmd(info);
			}
		}

		else if (interactive(info))
		{
			_putchar('\n');
		}

		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);

	if (!interactive(info) && info->status)
	{
		exit(info->status);
	}

	if (builtin_r == -2)
	{
		if (info->err_num == -1)
		{
			exit(info->status);
		}
		exit(info->err_num);
	}
	return (builtin_r);
}

/**
 * find_builtin - a func to find builtin
 * @info: param
 * Return: result
 */

int find_builtin(info_t *info)
{
	int f, built_in_r = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (f = 0; builtintbl[f].type; f++)
		if (_strcmp(info->argv[0], builtintbl[f].type) == 0)
		{
			info->line_count++;
			built_in_r = builtintbl[f].func(info);
			break;
		}
	return (built_in_r);
}

/**
 * find_cmd - a funct to find path of a command
 * @info: param
 * Return: none
 */

void find_cmd(info_t *info)
{
	char *path = NULL;
	int f, c;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (f = 0, c = 0; info->arg[f]; f++)
		if (!is_delim(info->arg[f], " \t\n"))
			c++;
	if (!c)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
		{
			fork_cmd(info);
		}
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - a function to fork an exe thread to run a command
 * @info: the param
 * Return: none
 */

void fork_cmd(info_t *info)
{
	pid_t child_pids;

	child_pids = fork();
	if (child_pids == -1)
	{
		perror("Error:");
		return;
	}

	if (child_pids == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
			{
				exit(126);
			}
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);

			if (info->status == 126)
			{
				print_error(info, "Permission denied\n");
			}
		}
	}
}
