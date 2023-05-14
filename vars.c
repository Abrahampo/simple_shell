#include "shell.h"

/**
 * is_chain - The chain delim that check if the curr character is in a buffer
 * @info: The structure that takes a parameter
 * @buf: This is just the character of a buffer
 * @p: The buffer that takes the address of a current position
 * Return: 1 for chain delim, else 0
 */

int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t aa = *p;

	if (buf[aa] == '|' && buf[aa + 1] == '|')
	{
		buf[aa] = 0;
		aa++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[aa] == '&' && buf[aa + 1] == '&')
	{
		buf[aa] = 0;
		aa++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[aa] == ';')
	{
		buf[aa] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = aa;
	return (1);
}

/**
 * check_chain - looks or find for continuing chain for last status
 * @info: This is the structure that takes a parameter
 * @buf: Just the chararacter of a buffer
 * @p: The buffer that takes the curr posi of a address.
 * @i: The buffer for the beginning position
 * @len: Just the buffer len or jsut length
 * Return: Just 0 or Void
 */

void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t aa = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			aa = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			aa = len;
		}
	}

	*p = aa;
}

/**
 * replace_alias - The string which relieve aliases of tokenz
 * @info: The structure which take the parameter
 * Return: 1 for relieve, else 0
 */

int replace_alias(info_t *info)
{
	int kk;
	list_t *knot;
	char *x;

	for (kk = 0; kk < 10; kk++)
	{
		knot = node_starts_with(info->alias, info->argv[0], '=');
		if (!knot)
			return (0);
		free(info->argv[0]);
		x = _strchr(knot->str, '=');
		if (!x)
			return (0);
		x = _strdup(x + 1);
		if (!x)
			return (0);
		info->argv[0] = x;
	}
	return (1);
}

/**
 * replace_vars - The string that relieve the tokenized variables
 * @info: The structure which takes the parameter
 * Return: 1 for relieve, else 0
 */

int replace_vars(info_t *info)
{
	int kk = 0;
	list_t *knot;

	for (kk = 0; info->argv[kk]; kk++)
	{
		if (info->argv[kk][0] != '$' || !info->argv[kk][1])
			continue;

		if (!_strcmp(info->argv[kk], "$?"))
		{
			replace_string(&(info->argv[kk]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[kk], "$$"))
		{
			replace_string(&(info->argv[kk]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		knot = node_starts_with(info->env, &info->argv[kk][1], '=');
		if (knot)
		{
			replace_string(&(info->argv[kk]),
					_strdup(_strchr(knot->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[kk], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - Relievs the str
 * @old: The string that takes the address of old.
 * @new: This is just the new string
 * Return: 1 for relieved, else 0
 */

int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
