#include "shell.h"

/**
 * is_cmd - The CMD which desire if a file or folder is executable  or not.
 * @info: This is just the structure information
 * @path: This is just the file path or way
 * Return: true if 1, else 0
 */

int is_cmd(info_t *info, char *path)
{
	struct stat k;
	(void)info;
	if (!path || stat(path, &k))
		return (0);
	if (k.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - The char or characters for duplication or Replication
 * @pathstr: This is just the string PATH or way
 * @start: The beginning or starting of the index
 * @stop: The index that is use for stopping
 * Return: The buffer that takes new pointer
 */

char *dup_chars(char *pathstr, int start, int stop)
{
	static char bb[1024];
	int pro = 0, vv = 0;

	for (vv = 0, pro = start; pro < stop; pro++)
		if (pathstr[pro] != ':')
			bb[vv++] = pathstr[pro];
	bb[vv] = 0;
	return (bb);
}

/**
 * find_path - This is the string which look for cammand in the PATH or way
 * @info: This is Just the structure for information
 * @pathstr: The string that takes the PATH
 * @cmd: The finding of a cammand line
 * Return: This just find if the PATH is full or NULL or not.
 */

char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int kk = 0, c_pro = 0;
	char *way;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[kk] || pathstr[kk] == ':')
		{
			way = dup_chars(pathstr, c_pro, kk);
			if (!*way)
				_strcat(way, cmd);
			else
			{
				_strcat(way, "/");
				_strcat(way, cmd);
			}
			if (is_cmd(info, way))
				return (way);
			if (!pathstr[kk])
				break;
			c_pro = kk;
		}
		kk++;
	}
	return (NULL);
}
