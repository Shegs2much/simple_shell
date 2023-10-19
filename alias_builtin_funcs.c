#include "shell.h"

int _shellby_alias(char **args, char __attribute__((__unused__)) **front);
void _set_alias(char *var_name, char *value);
void _print_alias(alias_t *alias);

/**
 * _shellby_alias - Builtin command that either print all aliases,
 * specific aliases, or sets an alias.
 * @args: An array of agruments
 * @front: A double pointer to the begining of the args
 *
 * Return: If an error occurs - -1.
 *	Otherwise - 0.
 */

int _shellby_alias(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *temp = aliases;
	int indx, rem = 0;
	char *value;

	if (!args[0])
	{
		while (temp)
		{
			_print_alias(temp);
			temp = temp->nxt;
		}
		return (rem);
	}
	for (indx = 0; args[indx]; indx++)
	{
		temp = aliases;
		value = _strchr(args[indx], '=');
		if (!value)
		{
			while (temp)
			{
				if (_strcmp(args[indx], temp->name) == 0)
				{
					_print_alias(temp);
					break;
				}
				temp = temp->nxt;
			}
			if (!temp)
				rem = _create_error(args + indx, 1);
		}
		else
			_set_alias(args[indx], value);
	}
	return (rem);
}

/**
 * _set_alias - Will either set an existing alias 'name' with a new value,
 * 'value' or creates a new alias with 'name' and 'value'
 * @var_name: Name of the alias
 * @value: Value of the alias. First character is a '='
 */

void _set_alias(char *var_name, char *value)
{
	alias_t *temp = aliases;
	int length, m, n;
	char *new_value;

	*value = '\0';
	value++;
	length = _strlen(value) - _strspn(value, "'\"");
	new_value = malloc(sizeof(char) * (length + 1));
	if (!new_value)
		return;
	for (m = 0, n = 0; value[m]; m++)
	{
		if (value[m] != '\'' && value[m] != '"')
			new_value[n++] = value[m];
	}
	new_value[n] = '\0';
	while (temp)
	{
		if (_strcmp(var_name, temp->name) == 0)
		{
			free(temp->value);
			temp->value = new_value;
			break;
		}
		temp = temp->nxt;
	}
	if (!temp)
		_add_alias_end(&aliases, var_name, new_value);
}

/**
 * _print_alias - Prints the alias in the format name='value'.
 * @alias: Pointer to an alias
 */

void _print_alias(alias_t *alias)
{
	char *alias_string;
	int length = _strlen(alias->name) + _strlen(alias->value) + 4;

	alias_string = malloc(sizeof(char) * (length + 1));
	if (!alias_string)
		return;
	_strcpy(alias_string, alias->name);
	_strcat(alias_string, "='");
	_strcat(alias_string, alias->value);
	_strcat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, length);
	free(alias_string);
}

/**
 * _replace_aliases - Goes through the arguments and replace any matching alias
 * with their value
 * @args: 2D pointer to the arguments
 *
 * Return: 2D pointer to the arguments
 */

char **_replace_aliases(char **args)
{
	alias_t *temp;
	int indx;
	char *new_value;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (indx = 0; args[indx]; indx++)
	{
		temp = aliases;
		while (temp)
		{
			if (_strcmp(args[indx], temp->name) == 0)
			{
				new_value = malloc(sizeof(char) * (_strlen(temp->value) + 1));
				if (!new_value)
				{
					_free_args(args, args);
					return (NULL);
				}
				_strcpy(new_value, temp->value);
				free(args[indx]);
				args[indx] = new_value;
				indx--;
				break;
			}
			temp = temp->nxt;
		}
	}
	return (args);
}
