#include "shell.h"

/**
 * list_len -  This is the length of linked list which determines
 * @h: The node of the start or first pointer
 * Return: Just the ist size or list size
 */
size_t list_len(const list_t *h)
{
	size_t kk = 0;

	while (h)
	{
		h = h->next;
		kk++;
	}
	return (kk);
}

/**
 * list_to_strings - The array of strs which returns the list->str
 * @head: The start or first node to the pointer
 * Return: just the array of a strs
 */

char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t kk = list_len(head), vv;
	char **ptr;
	char *str;

	if (!head || !kk)
		return (NULL);
	ptr = malloc(sizeof(char *) * (kk + 1));
	if (!ptr)
		return (NULL);
	for (kk = 0; node; node = node->next, kk++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (vv = 0; vv < kk; vv++)
				free(ptr[vv]);
			free(ptr);
			return (NULL);
		}
		str =_strcpy(str, node->str);
		ptr[kk] = str;
	}
	ptr[kk] = NULL;
	return (ptr);
}


/**
 * print_list - The list_t that prints all elements
 * @h: The start or first node to the pointer
 * Return: The list that takes the size.
 */

size_t print_list(const list_t *h)
{
	size_t kk = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		kk++;
	}
	return (kk);
}

/**
 * node_starts_with - The string that starts with the prefix with a node
 * whose returns
 * @node: The pointer that takes the list head.
 * @prefix: This just takes a strings
 * @c: The prefix of the next char.
 * Return: This just for the next match of nodes or node or null
 */

list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = starts_with(node->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - This takes or gets the indx of a nodes
 * @head: This is just the head of the pointer to a list
 * @node: The node to the pointer
 * Return:  1 is for indx node, else -1
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t kk = 0;

	while (head)
	{
		if (head == node)
			return (kk);
		head = head->next;
		kk++;
	}
	return (-1);
}
