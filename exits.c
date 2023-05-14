#include "shell.h"

/**
 **_strncpy - The string that is use to copy
 *@dest: Destination of string
 *@src: The source of a string
 *@n: The characters that is use to copy the amonut to
 *Return: The string is use for concatenating
 */
char *_strncpy(char *dest, char *src, int n)
{
	int k, v;
	char *u = dest;

	k = 0;
	while (src[k] != '\0' && k < n - 1)
	{
		dest[k] = src[k];
		k++;
	}
	if (k < n)
	{
		v = k;
		while (v < n)
		{
			dest[v] = '\0';
			v++;
		}
	}
	return (u);
}

/**
 * _strncat - The strings that are use for concatenating
 *@dest: The start string
 *@src: The end string
 *@n: The maximum amount of bytes that is used
 *Return: The string that is use for concatenating
 */

char *_strncat(char *dest, char *src, int n)
{
	int k, v;
	char *u = dest;

	k = 0;
	v = 0;
	while (dest[k] != '\0')
		k++;
	while (src[v] != '\0' && v < n)
	{
		dest[k] = src[v];
		k++;
		v++;
	}
	if (v < n)
		dest[k] = '\0';
	return (u);
}

/**
 **_strchr - The character that is found in a string
 *@s: The parsed string
 *@c: The character that is use for finding
 *Return: The pointer that shows the memory area
 */

char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
