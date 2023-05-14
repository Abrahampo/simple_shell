#include "shell.h"

/**
 * get_environ - String of array that copy and returns environment
 * @info: Structure containing potential arguments
 * A real prototype of the functions or function.
 * Return: just 0
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
 * _unsetenv - The environment that is used to delete a variable
 * @info: Structure containing potential arguments.
 * A real prototype of the functions or function.
 *  Return: 1 to delete, else 0
 * @var: just String environment of a variable of a property
 */

int _unsetenv(info_t *info, char *var)
{
	list_t *knot = info->env;
	size_t k = 0;
	char *pp;

	if (!knot || !var)
		return (0);
	while (knot)
	{
		pp = starts_with(knot->str, var);
		if (pp && *pp == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), k);
			k = 0;
			knot = info->env;
			continue;
		}
		knot = knot->next;
		k++;
	}
	return (info->env_changed);
}

/**
 * _setenv - An Initialization of a new environment to a variable
 * for modifying the one that is in existence
 * @info: Structure containing potential arguments.
 * A real prototype of the functions or function.
 * @var: The property of a string to an enveronment variable
 * @value: The enveronment variable of a string
 *  Return: just 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *bb = NULL;
	list_t *knot;
	char *pp;

	if (!var || !value)
		return (0);
	bb = malloc(_strlen(var) + _strlen(value) + 2);
	if (!bb)
		return (1);
	_strcpy(bb, var);
	_strcat(bb, "=");
	_strcat(bb, value);
	knot = info->env;
	while (knot)
	{
		pp = starts_with(knot->str, var);
		if (pp && *pp == '=')
		{
			free(knot->str);
			knot->str = bb;
			info->env_changed = 1;
			return (0);
		}
		knot = knot->next;
	}
	add_node_end(&(info->env), bb, 0);
	free(bb);
	info->env_changed = 1;
	return (0);
}
