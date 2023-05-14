#include "shell.h"

/**
 * _strlen - The string that is use to return the len val
 * @s: The len of string use for checking
 * Return: This is just the int len of the string
 */

int _strlen(char *s)
{
	int kk = 0;

	if (!s)
		return (0);

	while (*s++)
		kk++;
	return (kk);
}

/**
 * _strcmp - This carry out the lexicogarphic comparison of two strangs.
 * @s1: just the start or first str
 * @s2: This is just the end or second str
 * Return: nega for s1 < s2, pos for s1 > s2, null if s1 == s2
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - This is use for concat... strings
 * @dest: This is just the destination for buffer
 * @src: Just the buffer source
 * Return: The buffer that is use for pointer destination
 */

char *_strcat(char *dest, char *src)
{
	char *zz = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (zz);
}
