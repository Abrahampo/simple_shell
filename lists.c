#include "shell.h"

/**
 * add_node - It increase or add a node to the start of the list
 * @head: The node that takes the address of the pointer to the head
 * @str: The string that takes the field of a node
 * @num: The history that uses the indx of a node
 * Return: Just the list size
 */

list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *nn_hh;

	if (!head)
		return (NULL);
	nn_hh = malloc(sizeof(list_t));
	if (!nn_hh)
		return (NULL);
	_memset((void *)nn_hh, 0, sizeof(list_t));
	nn_hh->num = num;
	if (str)
	{
		nn_hh->str = _strdup(str);
		if (!nn_hh->str)
		{
			free(nn_hh);
			return (NULL);
		}
	}
	nn_hh->next = *head;
	*head = nn_hh;
	return (nn_hh);
}

/**
 * add_node_end - It increase or add a node to the finish or end of the list
 * @head: The node that takes the address of the pointer to the head
 * @str: The string that takes the field of a node
 * @num: The history that uses the indx of a node
 * Return: Just the size of the list
 */

list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *knot_new, *knot;

	if (!head)
		return (NULL);
	knot = *head;
	knot_new = malloc(sizeof(list_t));
	if (!knot_new)
		return (NULL);
	_memset((void *)knot_new, 0, sizeof(list_t));
	knot_new->num = num;
	if (str)
	{
		knot_new->str = _strdup(str);
		if (!knot_new->str)
		{
			free(knot_new);
			return (NULL);
		}
	}
	if (knot)
	{
		while (knot->next)
			knot = knot->next;
		knot->next = knot_new;
	}
	else
		*head = knot_new;
	return (knot_new);
}

/**
 * print_list_str - An element of a list_t that prints only the string
 * @h: The start or first node to the pointer
 * Return: just the size of the list
 */

size_t print_list_str(const list_t *h)
{
	size_t kk = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		kk++;
	}
	return (kk);
}

/**
 * delete_node_at_index - It traverse or deletes nodes or node at the raw indx
 * @head: The start or first node to the address of a pointer
 * @index: The indxs or index of a node that traverse or delete
 * Return: 1 for success, else 0 fails
 */

int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *knot, *pro;
	unsigned int kk = 0;

	if (!head || !*head)
		return (0);
	if (!index)
	{
		knot = *head;
		*head = (*head)->next;
		free(knot->str);
		free(knot);
		return (1);
	}
	knot = *head;
	while (knot)
	{
		if (kk == index)
		{
			pro->next = knot->next;
			free(knot->str);
			free(knot);
			return (1);
		}
		kk++;
		pro = knot;
		knot = knot->next;
	}
	return (0);
}

/**
 * free_list - The nodes that releases all list
 * @head_ptr: The node that takes the address of the pointer to the head
 * Return: just 0 or void
 */

void free_list(list_t **head_ptr)
{
	list_t *knot, *n_pro, *hh;

	if (!head_ptr || !*head_ptr)
		return;
	hh = *head_ptr;
	knot = hh;
	while (knot)
	{
		n_pro = knot->next;
		free(knot->str);
		free(knot);
		knot = n_pro;
	}
	*head_ptr = NULL;
}
