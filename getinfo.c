#include "shell.h"

/**
 * clear_info - The structure which uses info_t for initialization
 * @info: The sturcture that takes an address
 */

void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - The structure which uses info_t for initialization
 * @info: The sturcture that takes an address
 * @av: The vector that takes an argument
 */

void set_info(info_t *info, char **av)
{
	int kk = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (kk = 0; info->argv && info->argv[kk]; kk++)
			info->argc = kk;
		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - The structure ofinfo_t whic releases the fields or free
 * @info: The structure that takes an address
 * @all: Releases all fields if it is true.
 */

void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
		info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
