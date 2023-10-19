#include "shell.h"

char *_fill_path_dir(char *path);
list_t *_get_path_dir(char *path);

/**
 * _get_location - Locates a command in the PATH
 * @command: The command to locate
 *
 * Return: If an error occurs or the command connot be located - NULL
 * Otherwise - the full pathname of the command
 */

char *_get_location(char *command)
{
	char **path, *temp;
	struct stat st;
	list_t *dirs, *head;

	path = _getenv("PATH");
	if (!path || !(*path))
	{
		return (NULL);
	}

	dirs = _get_path_dir(*path + 5);
	head = dirs;

	while (dirs)
	{
		temp = malloc(_strlen(dirs->dir) + _strlen(command) + 2);
		if (!temp)
		{
			return (NULL);
		}

		_strcpy(temp, dirs->dir);
		_strcat(temp, "/");
		_strcat(temp, command);

		if (stat(temp, &st) == 0)
		{
			_free_list(head);
			return (temp);
		}

		dirs = dirs->nxt;
		free(temp);
	}

	_free_list(head);

	return (NULL);
}

/**
 * _fill_path_dir - Copies path but also replaces leading/sandwiched/trailing
 * colons (:) with the current directory
 * @path: The colon-separated list of directories
 *
 * Return: A copy of path with any leading/sandwiched/trailing colons replaced
 * with the current working directory
 */

char *_fill_path_dir(char *path)
{
	int indx, length = 0;
	char *path_dup, *pwd;

	pwd = *(_getenv("PWD")) + 4;
	for (indx = 0; path[indx]; indx++)
	{
		if (path[indx] == ':')
		{
			if (path[indx + 1] == ':' || indx == 0 || path[indx + 1] == '\0')
			{
				length += _strlen(pwd) + 1;
			}
			else
			{
				length++;
			}
		}
		else
		{
			length++;
		}
	}
	path_dup = malloc(sizeof(char) * (length + 1));
	if (!path_dup)
	{
		return (NULL);
	}
	path_dup[0] = '\0';
	for (indx = 0; path[indx]; indx++)
	{
		if (path[indx] == ':')
		{
			if (indx == 0)
			{
				_strcat(path_dup, pwd);
				_strcat(path_dup, ":");
			}
			else if (path[indx + 1] == ':' || path[indx + 1] == '\0')
			{
				_strcat(path_dup, ":");
				_strcat(path_dup, pwd);
			}
			else
			{
				_strcat(path_dup, ":");
			}
		}
		else
		{
			_strncat(path_dup, &path[indx], 1);
		}
	}
	return (path_dup);
}

/**
 * _get_path_dir - Tokenizes a colon-separated list of directories
 * into a list_s linked list
 * @path: The colon-separated list of directories
 *
 * Return: A pointer to the initialized linked list
 */

list_t *_get_path_dir(char *path)
{
	int indx;
	char **dirs, *path_dup;
	list_t *head = NULL;

	path_dup = _fill_path_dir(path);
	if (!path_dup)
	{
		return (NULL);
	}
	dirs = _strtok(path_dup, ":");
	free(path_dup);
	if (!dirs)
	{
		return (NULL);
	}

	for (indx = 0; dirs[indx]; indx++)
	{
		if (_add_node_end(&head, dirs[indx]) == NULL)
		{
			_free_list(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (head);
}
