#include "simple_shell.h"

/**
 * _list_len - Determines the length of linked list
 * @h: Pointer to the first node
 *
 * Return: Size of list
 */
size_t _list_len(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * list_to_strings - Returns an array of strings of the list->str
 * @head: Pointer to the first node
 *
 * Return: Array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = _list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_str_len(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * _print_list - Prints all elements of a list_t linked list
 * @h: Pointer to the first node
 *
 * Return: Size of list
 */
size_t _print_list(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * node_starts_with - Returns the node whose string starts with prefix
 * @node: Pointer to the list head
 * @prefix: String to match
 * @c: The next character after prefix to match
 *
 * Return: Match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * _get_node_index - Gets the index of the node
 * @head: Pointer to the list head
 * @node: Pointer to the node
 *
 * Return: Index of node or -1
 */
ssize_t _get_node_index(list_t *head, list_t *node)
{
	size_t j = 0;

	while (head)
	{
		if (head == node)
			return (j);
		head = head->next;
		j++;
	}
	return (-1);
}