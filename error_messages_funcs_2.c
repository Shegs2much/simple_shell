#include "shell.h"

char *_error_126(char **args);
char *_error_127(char **args);

/**
 * _error_126 - Creates an error message for permission denied errors
 * @args: An array of arguments passed to the command
 *
 * Return: The error string
 */

char *_error_126(char **args)
{
	int length;
	char *error, *history_str;

	history_str = itoa(hist);
	if (!history_str)
	{
		return (NULL);
	}

	length = _strlen(name) + _strlen(history_str) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(history_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, history_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Permission denied\n");

	free(history_str);
	return (error);
}

/**
 * _error_127 - Creates an error message for the command not found errors
 * @args: Array of arguments passed to the command
 *
 * Return: The error string
 */

char *_error_127(char **args)
{
	int length;
	char *error, *history_str;

	history_str = itoa(hist);
	if (!history_str)
	{
		return (NULL);
	}

	length = _strlen(name) + _strlen(history_str) + _strlen(args[0]) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(history_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, history_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": not found\n");

	free(history_str);
	return (error);
}
