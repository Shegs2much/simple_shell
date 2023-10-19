#include "shell.h"

char *_error_env(char **args);
char *_error_1(char **args);
char *_error_2_syntax(char **args);
char *_error_2_cd(char **args);
char *_error_2_exit(char **args);

/**
 * _error_env - Creates an error message for _shellby_env errors
 * @args: Array of arguments passed to the command
 *
 * Return: The error string
 */

char *_error_env(char **args)
{
	int length;
	char *error, *history_str;

	history_str = itoa(hist);
	if (!history_str)
		return (NULL);

	args--;
	length = _strlen(name) + _strlen(history_str) + _strlen(args[0]) + 45;
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
	_strcat(error, ": Unable to add/remove from environment\n");

	free(history_str);
	return (error);
}

/**
 * _error_1 - Creates an error message for _shellby_alias errors
 * @args: Array of arguments passed to the command
 *
 * Return: The error string
 */

char *_error_1(char **args)
{
	int length;
	char *error;

	length = _strlen(name) + _strlen(args[0]) + 13;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
		return (NULL);

	_strcpy(error, "alias: ");
	_strcat(error, args[0]);
	_strcat(error, " not found\n");

	return (error);
}

/**
 * _error_2_syntax - Creates an error message for syntax errors
 * @args: An array of arguments passed to the command
 *
 * Return: The error string
 */

char *_error_2_syntax(char **args)
{
	int length;
	char *error, *history_str;

	history_str = itoa(hist);
	if (!history_str)
	{
		return (NULL);
	}

	length = _strlen(name) + _strlen(history_str) + _strlen(args[0]) + 33;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(history_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, history_str);
	_strcat(error, ": Syntax error: \"");
	_strcat(error, args[0]);
	_strcat(error, "\" unexpected\n");

	free(history_str);
	return (error);
}

/**
 * _error_2_cd - Creates an error message for _shellby_cd errors
 * @args: Array of arguments passed to the command
 *
 * Return: The error string
 */

char *_error_2_cd(char **args)
{
	int length;
	char *error, *history_str;

	history_str = itoa(hist);
	if (!history_str)
	{
		return (NULL);
	}

	if (args[0][0] == '-')
		args[0][2] = '\0';
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
	if (args[0][0] == '-')
	{
		_strcat(error, ": cd: Illegal option ");
	}
	else
	{
		_strcat(error, ": cd: can't cd to ");
	}
	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(history_str);
	return (error);
}

/**
 * _error_2_exit - Creates an error message for _shellby_exit errors
 * @args: Array of arguments passed to the command
 *
 * Return: The error string
 */

char *_error_2_exit(char **args)
{
	int length;
	char *error, *history_str;

	history_str = itoa(hist);
	if (!history_str)
	{
		return (NULL);
	}

	length = _strlen(name) + _strlen(history_str) + _strlen(args[0]) + 27;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(history_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, history_str);
	_strcat(error, ": exit: Illegal number: ");
	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(history_str);
	return (error);
}
