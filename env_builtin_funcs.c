#include "shell.h"

int _shellby_env(char **args, char __attribute__((__unused__)) **front);
int _shellby_unsetenv(char **args, char __attribute__((__unused__)) **fornt);
int _shellby_setenv(char **args, char __attribute__((__unused__)) **front);

/**
 * _shellby_env - Prints the current environment
 * @args: Array of arguments passed to the shell
 * @front: A double pointer to tthe beginning of args
 *
 * Return: If error occurs, -1
 * Otherwise, 0
 *
 * Description: Prints one variable per line using the
 * format 'variable'='value'
 */

int _shellby_env(char **args, char __attribute__((__unused__)) **front)
{
	char nc = '\n';
	int indx;

	if (!environ)
		return (-1);

	for (indx = 0; environ[indx]; indx++)
	{
		write(STDOUT_FILENO, environ[indx], _strlen(environ[indx]));
		write(STDOUT_FILENO, &nc, 1);
	}

	(void)args;
	return (0);
}

/**
 * _shellby_unsetenv - Deletes an environmental variable from the PATH
 * @args: Array of arguments passed to the shell
 * @front: A double pointer to the beginning of args
 *
 * Return: If an error occurs, -1
 * Otherwise, 0
 *
 * Description: args[1] is the variable to remove from the PATH
 */

int _shellby_unsetenv(char **args, char __attribute__((__unused__)) **front)
{
	size_t size;
	int indx, indx2;
	char **env_var, **new_environ;

	if (!args[0])
		return (_create_error(args, -1));
	env_var = _getenv(args[0]);
	if (!env_var)
		return (0);

	for (size = 0; environ[size]; size++)
	{
		;
	}

	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (_create_error(args, -1));

	for (indx = 0, indx2 = 0; environ[indx]; indx++)
	{
		if (*env_var == environ[indx])
		{
			free(*env_var);
			continue;
		}
		new_environ[indx2] = environ[indx];
		indx2++;
	}
	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;

	return (0);
}

/**
 * _shellby_setenv - Changes or adds an environmental variable to the PATH
 * @args: Array of arguments passed to the shell
 * @front: A double pointer to the beginning of args
 *
 * Return: If an error occurs, -1
 * Otherwise, 0
 *
 * Description: args[1] is the name of the new or existing PATH variable
 * args[2] is the value to set the new or changed variable to
 */

int _shellby_setenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var = NULL, **new_environ, *new_value;
	int indx;
	size_t size;

	if (!args[0] || !args[1])
		return (_create_error(args, -1));

	new_value = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_value)
		return (_create_error(args, -1));
	_strcpy(new_value, args[0]);
	_strcat(new_value, "=");
	_strcat(new_value, args[1]);

	env_var = _getenv(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}
	for (size = 0; environ[size]; size++)
	{
		;
	}

	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(new_value);
		return (_create_error(args, -1));
	}

	for (indx = 0; environ[indx]; indx++)
	{
		new_environ[indx] = environ[indx];
	}

	free(environ);
	environ = new_environ;
	environ[indx] = new_value;
	environ[indx + 1] = NULL;

	return (0);
}
