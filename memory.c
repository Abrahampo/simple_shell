#include "shell.h"

/**
 * bfree - This is the address whcih releases the address of pointer to NULL
 * @ptr: This Just release the addr of a pointer
 * Return: 1 to release, else 0.
 */

int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
