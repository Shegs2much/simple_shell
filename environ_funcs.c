#include "shell.h"

void free_env(void);
char **_copyenv(void);
char **_getenv(const char *var);

/**
 * free_env - Frees the environment copy
 */

void free_env(void)
{
	int indx;

	for (indx = 0; environ[indx]; indx++)
	{
		free(environ[indx]);
	}
	free(environ);
}

/**
 * _copyenv - Creates a copy of the environment
 *
 * Return: If an error occurs, NULL
 * Otherwise, a double pointer to the new copy
 */

char **_copyenv(void)
{
	int indx;
	char **new_environ;
	size_t size;

	for (size = 0; environ[size]; size++)
	{
		;
	}

	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
		return (NULL);

	for (indx = 0; environ[indx]; indx++)
	{
		new_environ[indx] = malloc(_strlen(environ[indx]) + 1);

		if (!new_environ[indx])
		{
			for (indx--; indx >= 0; indx--)
			{
				free(new_environ[indx]);
			}
			free(new_environ);
			return (NULL);
		}
		_strcpy(new_environ[indx], environ[indx]);
	}
	new_environ[indx] = NULL;

	return (new_environ);
}

/**
 * _getenv - Gets an environmental variable from the PATH
 * @var: Name of the environmental variable to get
 *
 * Return: If the environmental variable does not exist - NULL
 * Otherwise - a pointer to the environmental variable
 */

char **_getenv(const char *var)
{
	int indx, length;

	length = _strlen(var);
	for (indx = 0; environ[indx]; indx++)
	{
		if (_strncmp(var, environ[indx], length) == 0)
			return (&environ[indx]);
	}

	return (NULL);
}
