#include "shell.h"

#include <unistd.h>
#include <ctype.h>

/**
 * interactive - An interactive mode that returns shell if it is true
 * @info: the address of the structure
 * Return: 1 is interactive mode, 0 else
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - the character that checks if it is a delimeter
 * @c: A chararacter that is used to check
 * @delim: Just Delimeter of the string
 * Return: 1 is true, else 0 is false
 */

int is_delim(char c, char *delim)
{
	while (*delim != '\0')
	{
		if (*delim == c)
			return (1);
	delim++;
	}
	return (0);
}

/**
 * _isalpha - An alphabet that checks the character
 * @c: The C character to take input
 * Return: 1 if is alphabet, 0 else
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - the converter that takes string as integer
 * @s: A converted string
 * Return: 0 for numbers in string,  else the converted number
 */
int _atoi(char *s)
{
	int k, pro = 1, fg = 0, add;
	unsigned int outcome = 0;

	for (k = 0; s[k] != '\0' && fg != 2; k++)
	{
		if (s[k] == '-')
			pro *= -1;
		if (s[k] >= '0' && s[k] <= '9')
		{
			fg = 1;
			outcome *= 10;
			outcome += (s[k] - '0');
		}
		else if (fg == 1)
			fg = 2;
	}
	if (pro == -1)
		add = -outcome;
	else
		add = outcome;
	return (add);
}
