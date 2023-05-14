#include "shell.h"

/**
 * hsh - Just the shell for looping.
 * @info: The structure that is use to return the info and the parameter
 * @av: Just the arg for vector of main function
 * Return: just 0 for success, and 1 for error
 */

int hsh(info_t *info, char **av)
{
	ssize_t vv = 0;
	int bb_r = 0;

	while (vv != -1 && bb_r != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		bb_r = get_input(info);
		if (vv != -1)
		{
			set_info(info, av);
			bb_r = find_builtin(info);
			if (bb_r == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (bb_r == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (bb_r);
}

/**
 * find_builtin - Just the cmd that is use to find the builtin
 * @info: The structure that is use to return the information and parameter
 * Return: This -1 for builtin if not available or found
 * 0 for builtin  run good
 * 1 for builtin available but not good
 * 2 for builtin sig exit()
 */

int find_builtin(info_t *info)
{
	int kk, bb = -1;
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

	for (kk = 0; builtintbl[kk].type; kk++)
		if (_strcmp(info->argv[0], builtintbl[kk].type) == 0)
		{
			info->line_count++;
			bb = builtintbl[kk].func(info);
			break;
		}
	return (bb);
}

/**
 * find_cmd - The command that is use to look or find the PATH
 * @info: The structure that is use to return the information and the parameter
 * Return: just 0 or void
 */

void find_cmd(info_t *info)
{
	char *path = NULL;
	int knot, vv;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (knot = 0, vv = 0; info->arg[knot]; knot++)
		if (!is_delim(info->arg[knot], " \t\n"))
			vv++;
	if (!vv)
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
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - The cammand that runs the executioner thread for forks_cmd.
 * @info: The structure that takes and retuns the info and parameter
 * Return: just 0 or void
 */

void fork_cmd(info_t *info)
{
	pid_t zz;

	zz = fork();
	if (zz == -1)
	{
		perror("Error:");
		return;
	}
	if (zz == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
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
				print_error(info, "Permission denied\n");
		}
	}
}
