#include "shell.h"

/**
 * _memset - This is just the constant byte which fills the memory.
 * @s: The memory that takes the area of a pointer
 * @b: This is just the *s wihch fills the bytes or byte
 * @n: Just the bytes to fill the amount
 * Return: Just the memory area of a pointer for s
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int kk;

	for (kk = 0; kk < n; kk++)
		s[kk] = b;
	return (s);
}

/**
 * ffree - This just release a str or strs
 * @pp: Just the str of a strs
 */

void ffree(char **pp)
{
	char **zz = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(zz);
}

/**
 * _realloc - This is the block of memory for reallocation
 * @ptr: Just the malloc'ated block of a pointer
 * @old_size: Just the block of byte or bytes size for pre.
 * @new_size: The byte size for a new block
 * Return: Just the da ol'block for the pointer name
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *uu;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);
	uu = malloc(new_size);
	if (!uu)
		return (NULL);
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		uu[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (uu);
}
