#include "shell.h"

/**
 * is_cmd - a func to see if a file is a .exe
 * @info: the info var
 * @path: file path var
 * Return: result.
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
	{
		return (0);
	}

	if (st.st_mode & S_IFREG)
		return (1);
	return (0);
}
/**
 * dup_chars - a function to dupe char
 * @pathstr: str paths
 * @start: start pos
 * @stop: stop pos
 * Return: ptr
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int j = 0;
	int c = 0;

	for (c = 0, j = start; j < stop; j++)
	{
		if (pathstr[j] != ':')
		{
			buf[c++] = pathstr[j];
		}
	}
	buf[c] = 0;
	return (buf);
}

/**
 * find_path - a function to finds path
 * @info: struct info
 * @pathstr: path str
 * @cmd: search comm
 * Return: results of command
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int j = 0, current_posi = 0;
	char *path;

	if (!pathstr)
	{
		return (NULL);
	}
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
		{
			return (cmd);
		}
	}
	while (1)
	{
		if (!pathstr[j] || pathstr[j] == ':')
		{
			path = dup_chars(pathstr, current_posi, j);
			if (!*path)
			{
				_strcat(path, cmd);
			}
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[j])
				break;
			current_posi = j;
		}
		j++;
	}
	return (NULL);
}
