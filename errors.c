#include "shell.h"

/**
 * _eputs - The iput of string to be printed
 * @str: the printed string
 * Return: None
 */

void _eputs(char *str)
{
	int k = 0;

	if (!str)
		return;
	while (str[k] != '\0')
	{
		_eputchar(str[k]);
		k++;
	}
}

/**
 * _eputchar - The character that writes the stderrors
 * @c: The printed character
 * Return: 1 for success.
 * if error, -1 is returned, or errno is set precisely.
 */

int _eputchar(char c)
{
	static int k;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(2, buffer, k);
		k = 0;
	}
	if (c != BUF_FLUSH)
		buffer[k++] = c;
	return (1);
}

/**
 * _putfd - the filedescriptor that  writes the character
 * @c: This is just the character to be printed
 * @fd: The filedescriptor
 * Return: 1 for success.
 * if error, -1 is returned, or errno is set precisely.
 */

int _putfd(char c, int fd)
{
	static int k;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(fd, buffer, k);
		k = 0;
	}
	if (c != BUF_FLUSH)
		buffer[k++] = c;
	return (1);
}

/**
 * _putsfd - The input of string to be printed
 * @str: the printed string
 * @fd: The filedescriptor
 *
 * Return: The numbers or number of chars
 */
int _putsfd(char *str, int fd)
{
	int k = 0;

	if (!str)
		return (0);
	while (*str)
	{
		k += _putfd(*str++, fd);
	}
	return (k);
}
