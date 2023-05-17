#include "shell.h"

/**
 * _myenv - the resent environment to be printed
 * @info: Structure containing potential arguments. Used to maintain
 *  A real prototype of the functions or function.
 * Return: just 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - the environ that gets the variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: environment variable name
 *
 * Return: just the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *knots = info->env;
	char *pointer;

	while (knots)
	{
		pointer = starts_with(knots->str, name);
		if (pointer && *pointer)
			return (pointer);
		knots = knots->next;
	}
	return (NULL);
}

/**
 * _mysetenv - The Initialization of environmental variable
 * modifying an exiting mode
 * @info: Structuure containing potential arguments.
 * A real prototype of the functions or function.
 * Return: just 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Wrong number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - The environment that delete or traverse a variable
 * @info: Structure containing potential arguments. Used to maintain
 * A real prototype of the functions or function.
 * Return: just 0
 */
int _myunsetenv(info_t *info)
{
	int k;

	if (info->argc == 1)
	{
		_eputs(" few arguements.\n");
		return (1);
	}
	for (k = 1; k <= info->argc; k++)
		_unsetenv(info, info->argv[k]);

	return (0);
}

/**
 * populate_env_list - A listed that populates the enviroment
 * @info: Structure containing potential argumets.
 * A real prototype of the functions and function.
 * Return: just 0
 */
int populate_env_list(info_t *info)
{
	list_t *knots = NULL;
	size_t k;

	for (k = 0; environ[k]; k++)
		add_node_end(&knots, environ[k], 0);
	info->env = knots;
	return (0);
}

