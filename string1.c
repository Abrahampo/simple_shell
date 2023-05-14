#include "shell.h"

/**
 * _strcpy - This just copy the string
 * @dest: Just for destination
 * @src: Just the source
 * Return: This is the pointer for destination
 */

char *_strcpy(char *dest, char *src)
{
	int kk = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[kk])
	{
		dest[kk] = src[kk];
		kk++;
	}
	dest[kk] = 0;
	return (dest);
}

/**
 * _strdup - just the string that is use for duplicating
 * @str: Just the duplicated string
 * Return: This is just the pointer that is use for duplicating a str
 */
char *_strdup(const char *str)
{
	int len_g = 0;
	char *vv;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len_g++;
	vv = malloc(sizeof(char) * (len_g + 1));
	if (!vv)
		return (NULL);
	for (len_g++; len_g--;)
		vv[len_g] = *--str;
	return (vv);
}

/**
 * _puts - Just the string use for printing an inout
 * @str: Just the printed string
 * Return: 0
 */

void _puts(char *str)
{
	int kk = 0;

	if (!str)
		return;
	while (str[kk] != '\0')
	{
		_putchar(str[kk]);
		kk++;
	}
}

/**
 * _putchar - This is the char use to write standardoutput in C prog
 * @c: Ths is just char that is use for printing
 * Return: 1 just for success
 *  when error, -1 for returned, else err is in precisely.
 */

int _putchar(char c)
{
	static int kk;
	static char bb[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || kk >= WRITE_BUF_SIZE)
	{
		write(1, bb, kk);
		kk = 0;
	}
	if (c != BUF_FLUSH)
		bb[kk++] = c;
	return (1);
}
