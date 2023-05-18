#include "shell.h"

/**
 * _myhistory - history list for sharing one single by line
 * A numbers starting at 0.
 * @info:  It is Used to maintain structure that have the real arg.
 * A real prototype of the functions or function.
 *  Return: just 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - assig a string to alias or alias to string
 * @info: the sturcutr of the parameter
 * @str: alias of string or string of alias
 * Return: just 0 for success, 1 for errors
 */

int unset_alias(info_t *info, char *str)
{
	char *pointer, k;
	int v;

	pointer = _strchr(str, '=');
	if (!pointer)
		return (1);
	k = *pointer;
	*pointer = 0;
	v = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*pointer = k;
	return (v);
}

/**
 * set_alias - assig a string to alias or alias to string
 * @info: the sturcutr of the parameter
 * @str: alias of string or string of alias
 *
 * Return: just 0 for success, 1 for errors
 */
int set_alias(info_t *info, char *str)
{
	char *pointer;

	pointer = _strchr(str, '=');
	if (!pointer)
		return (1);
	if (!*++pointer)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - result of an alias of string
 * @node: the number alias of node
 * Return: just 0 for success, 1 for errors
 */
int print_alias(list_t *node)
{
	char *pointer = NULL, *u = NULL;

	if (node)
	{
		pointer = _strchr(node->str, '=');
		for (u = node->str; u <= pointer; u++)
		_putchar(*u);
		_putchar('\'');
		_puts(pointer + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - the alias that contain the builtin mimics
 * @info: It is Used to maintain structure that have the real arg.
 * A real prototype of the functions or function.
 *  Return: just 0
 */
int _myalias(info_t *info)
{
	int integer = 0;
	char *pointer = NULL;
	list_t *knots = NULL;

	if (info->argc == 1)
	{
		knots = info->alias;
		while (knots)
		{
			print_alias(knots);
			knots = knots->next;
		}
		return (0);
	}
	for (integer = 1; info->argv[integer]; integer++)
	{
		pointer = _strchr(info->argv[integer], '=');
		if (pointer)
			set_alias(info, info->argv[integer]);
		else
			print_alias(node_starts_with(info->alias, info->argv[integer], '='));
	}

	return (0);
}

