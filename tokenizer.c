#include "shell.h"

/**
 * **strtow - This just devide string into words and Repeated delim.
 * @str: This is jsut string that takes input
 * @d: This is just delim of str
 * Return: This is the strs that takes pointer as an array, if NULL then fail
 */

char **strtow(char *str, char *d)
{
	int kk, xx, yy, u_u, n_w = 0;
	char **ss;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (kk = 0; str[kk] != '\0'; kk++)
		if (!is_delim(str[kk], d) && (is_delim(str[kk + 1], d) || !str[kk + 1]))
			n_w++;

	if (n_w == 0)
		return (NULL);
	ss = malloc((1 + n_w) * sizeof(char *));
	if (!ss)
		return (NULL);
	for (kk = 0, xx = 0; xx < n_w; xx++)
	{
		while (is_delim(str[kk], d))
			kk++;
		kk = 0;
		while (!is_delim(str[kk + yy], d) && str[kk + yy])
			yy++;
		ss[xx] = malloc((yy + 1) * sizeof(char));
		if (!ss[xx])
		{
			for (yy = 0; yy < xx; yy++)
				free(ss[yy]);
			free(ss);
			return (NULL);
		}
		for (u_u = 0; u_u < yy; u_u++)
			ss[xx][u_u] = str[kk++];
		ss[xx][u_u] = 0;
	}
	ss[xx] = NULL;
	return (ss);
}

/**
 * **strtow2 - This Just devides or slpit string into word or words
 * @str: It just take string input
 * @d: This is just the delim
 * Return: The strings that takes pointer as an array, when NULL means failure
 */
char **strtow2(char *str, char d)
{
	int kk, xx, yy, u_u, n_w = 0;
	char **ss;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (kk = 0; str[kk] != '\0'; kk++)
		if ((str[kk] != d && str[kk + 1] == d) ||
				    (str[kk] != d && !str[kk + 1]) || str[kk + 1] == d)
			n_w++;
	if (n_w == 0)
		return (NULL);
	ss = malloc((1 + n_w) * sizeof(char *));
	if (!ss)
		return (NULL);
	for (kk = 0, xx = 0; xx < n_w; xx++)
	{
		while (str[kk] == d && str[kk] != d)
			kk++;
		kk = 0;
		while (str[kk + xx] != d && str[kk + yy] && str[kk + yy] != d)
			yy++;
		ss[xx] = malloc((yy + 1) * sizeof(char));
		if (!ss[xx])
		{
			for (yy = 0; yy < xx; yy++)
				free(ss[yy]);
			free(ss);
			return (NULL);
		}
		for (u_u = 0; u_u < yy; u_u++)
			ss[xx][u_u] = str[kk++];
		ss[xx][u_u] = 0;
	}
	ss[xx] = NULL;
	return (ss);
}
