#include "shell.h"

/**
 * _myexit - to leave or exit the shell
 * @info: It is Used to maintain structure that have the real arg
 * A real prototype of the functions or function
 * Return: leave exit status or mode
 * (0) if info.argv[0] != "exit"
 */

int _myexit(info_t *info)
{
	int leave;

	if (info->argv[1])
	{
		leave = _erratoi(info->argv[1]);
		if (leave == -1)
		{
			info->status = 2;
			print_error(info, "fake number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - The process or opp that changes the directory
 * @info: It is Used to maintain structure that have the real arg
 * A real prototype of the functions or function
 * Return: just 0
 */
int _mycd(info_t *info)
{
	char *kk, *path, buffer[1024];
	int ch_d;

	kk = getcwd(buffer, 1024);
	if (!kk)
		_puts("TODO: >>getcwd fails messages<<\n");
	if (!info->argv[1])
	{
		path = _getenv(info, "HOME=");
		if (!path)
			ch_d =
				chdir((path = _getenv(info, "PWD=")) ? path : "/");
		else
			ch_d = chdir(path);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(kk);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		ch_d =
			chdir((path = _getenv(info, "OLDPWD=")) ? path : "/");
	}
	else
		ch_d = chdir(info->argv[1]);
	if (ch_d == -1)
	{
		print_error(info, " cd can't");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - the process of changing the present dir
 * @info: It is Used to maintain structure that have the real arg.
 * A real prototype of the functions or function
 * Return: just 0
 */
int _myhelp(info_t *info)
{
	char **A;

	A = info->argv;
	_puts("Function for doing it or yet \n");
	if (0)
		_puts(*A);
	return (0);
}
