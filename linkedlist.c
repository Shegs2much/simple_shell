#include "shell.h"

void _free_list(list_t *head);
void _free_alias_list(alias_t *head);
list_t *_add_node_end(list_t **head, char *dir);
alias_t *_add_alias_end(alias_t **head, char *name, char *value);

/**
 * _free_list - Frees a list_t linked list
 * @head: The head of the list_t list
 */

void _free_list(list_t *head)
{
	list_t *nxt;

	while (head)
	{
		nxt = head->nxt;
		free(head->dir);
		free(head);
		head = nxt;
	}
}

/**
 * _free_alias_list - Frees a alias_t linked list
 * @head: The head of the alias_t list
 */

void _free_alias_list(alias_t *head)
{
	alias_t *nxt;

	while (head)
	{
		nxt = head->nxt;
		free(head->name);
		free(head->value);
		free(head);
		head = nxt;
	}
}

/**
 * _add_node_end - Adds a node to the end of a list_t linked list
 * @head: A pointer to the head of the list_t list
 * @dir: The directory oath for the new node to contain
 *
 * Return: If an error occurs - NULL
 * Otherwise - a pointer to the new node
 */

list_t *_add_node_end(list_t **head, char *dir)
{
	list_t *new_node = malloc(sizeof(list_t));
	list_t *last;

	if (!new_node)
	{
		return (NULL);
	}

	new_node->dir = dir;
	new_node->nxt = NULL;

	if (*head)
	{
		last = *head;
		while (last->nxt != NULL)
			last = last->nxt;
		last->nxt = new_node;
	}
	else
	{
		*head = new_node;
	}

	return (new_node);
}

/**
 * _add_alias_end - Adds a node to the end of a alias_t linked list
 * @head: A pointer to the head of the list_t list
 * @name: The name if the new alias to be added
 * @value: The value of the new alias to be added
 *
 * Return: If an error occurs - NULL
 * Otherwise - a pointer to the new node
 */

alias_t *_add_alias_end(alias_t **head, char *name, char *value)
{
	alias_t *new_node = malloc(sizeof(alias_t));
	alias_t *last;

	if (!new_node)
	{
		return (NULL);
	}

	new_node->nxt = NULL;
	new_node->name = malloc(sizeof(char) * (_strlen(name) + 1));
	if (!new_node->name)
	{
		free(new_node);
		return (NULL);
	}
	new_node->value = value;
	_strcpy(new_node->name, name);

	if (*head)
	{
		last = *head;
		while (last->nxt != NULL)
			last = last->nxt;
		last->nxt = new_node;
	}
	else
	{
		*head = new_node;
	}

	return (new_node);
}
