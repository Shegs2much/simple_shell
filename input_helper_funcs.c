#include "shell.h"

int _check_args(char **args);
int _handle_args(int *exe_retr);
char *_get_args(char *line, int *exe_retr);
int _call_args(char **args, char **front, int *exe_retr);
int _run_args(char **args, char **front, int *exe_retr);

/**
 * _check_args - Checks if there are any leading ';', ';;', '&&', or '||'
 * @args: Double pointer to tokenized commands and arguments
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid position, 2
 * Otherwise, 0
 */

int _check_args(char **args)
{
	size_t indx;
	char *curr, *nxt;

	for (indx = 0; args[indx]; indx++)
	{
		curr = args[indx];
		if (curr[0] == ';' || curr[0] == '&' || curr[0] == '|')
		{
			if (indx == 0 || curr[1] == ';')
			{
				return (_create_error(&args[indx], 2));
			}
			nxt = args[indx + 1];
			if (nxt && (nxt[0] == ';' || nxt[0] == '&' || nxt[0] == '|'))
			{
				return (_create_error(&args[indx + 1], 2));
			}
		}
	}
	return (0);
}

/**
 * _handle_args - Gets, calls, and runs the execution of a command
 * @exe_retr: The return value of the parent process's last executed
 * command
 *
 * Return: If an end-of-file is read - END_OF_FILE (-2)
 * If the input cannot be tokenized - -1
 * Otherwise - The exit value of the last executed command
 */

int _handle_args(int *exe_retr)
{
	int rem = 0, indx;
	char **args, *line = NULL, **front;

	line = _get_args(line, exe_retr);
	if (!line)
	{
		return (END_OF_FILE);
	}

	args = _strtok(line, " ");
	free(line);
	if (!args)
	{
		return (rem);
	}
	if (_check_args(args) != 0)
	{
		*exe_retr = 2;
		_free_args(args, args);
		return (*exe_retr);
	}
	front = args;

	for (indx = 0; args[indx]; indx++)
	{
		if (_strncmp(args[indx], ";", 1) == 0)
		{
			free(args[indx]);
			args[indx] = NULL;
			rem = _call_args(args, front, exe_retr);
			args = &args[++indx];
			indx = 0;
		}
	}
	if (args)
	{
		rem = _call_args(args, front, exe_retr);
	}

	free(front);
	return (rem);
}

/**
 * _get_args - Gets a command from standard input
 * @line: A buffer to store the command
 * @exe_retr: The return value of the last executed command
 *
 * Return: If an error occurs - NULL
 * Otherwise - a pointer to the stored command
 */

char *_get_args(char *line, int *exe_retr)
{
	size_t m = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (line)
	{
		free(line);
	}

	read = _getline(&line, &m, STDIN_FILENO);
	if (read == -1)
	{
		return (NULL);
	}
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, prompt, 2);
		}
		return (_get_args(line, exe_retr));
	}

	line[read - 1] =  '\0';
	_replace_variable(&line, exe_retr);
	_handle_line(&line, read);

	return (line);
}

/**
 * _call_args - Partitions operators from commands and calls them
 * @args: Array of arguments
 * @front: A double pointer to the beginning of args
 * @exe_retr: The return value of the parent process' last executed
 * command
 *
 * Return: The return value of the last executed command
 */

int _call_args(char **args, char **front, int *exe_retr)
{
	int rem, indx;

	if (!args[0])
	{
		return (*exe_retr);
	}
	for (indx = 0; args[indx]; indx++)
	{
		if (_strncmp(args[indx], "||", 2) == 0)
		{
			free(args[indx]);
			args[indx] = NULL;
			args = _replace_aliases(args);
			rem = _run_args(args, front, exe_retr);
			if (*exe_retr != 0)
			{
				args = &args[++indx];
				indx = 0;
			}
			else
			{
				for (indx++; args[indx]; indx++)
				{
					free(args[indx]);
				}
				return (rem);
			}
		}
		else if (_strncmp(args[indx], "&&", 2) == 0)
		{
			free(args[indx]);
			args[indx] = NULL;
			args = _replace_aliases(args);
			rem = _run_args(args, front, exe_retr);
			if (*exe_retr == 0)
			{
				args = &args[++indx];
				indx = 0;
			}
			else
			{
				for (indx++; args[indx]; indx++)
				{
					free(args[indx]);
				}
				return (rem);
			}
		}
	}
	args = _replace_aliases(args);
	rem = _run_args(args, front, exe_retr);
	return (rem);
}

/**
 * _run_args - Calls the execution of a command
 * @args: Array of arguments
 * @front: Double pointer to the beginning of args
 * @exe_retr: The return value of the parent process' last executed
 * command
 *
 * Return: Th return value of the last executed command
 */

int _run_args(char **args, char **front, int *exe_retr)
{
	int rem, indx;
	int (*builtin)(char **args, char **front);

	builtin = _get_builtin(args[0]);

	if (builtin)
	{
		rem = builtin(args + 1, front);
		if (rem != EXIT)
		{
			*exe_retr = rem;
		}
	}
	else
	{
		*exe_retr = _execute(args, front);
		rem = *exe_retr;
	}

	hist++;

	for (indx = 0; args[indx]; indx++)
	{
		free(args[indx]);
	}

	return (rem);
}
