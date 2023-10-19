#include "shell.h"

void _sig_handler(int sig);
int _execute(char **args, char **front);

/**
 * _sig_handler - Prints a new prompt upon a signal
 * @sig: The signal
 */

void _sig_handler(int sig)
{
	char *new_prompt = "\n$ ";

	(void)sig;
	signal(SIGINT, _sig_handler);
	write(STDIN_FILENO, new_prompt, 3);
}

/**
 * _execute - Executes a command in a child process
 * @args: Array of arguments
 * @front: A double pointer to the beginning of args
 *
 * Return: If an error occurs - a corresponding error
 * code
 * Otherwise - The exit value of the last executed command
 */

int _execute(char **args, char **front)
{
	int stat, flag = 0, rem = 0;
	char *command = args[0];
	pid_t child_pid;

	if (command[0] != '/' && command[0] != '.')
	{
		flag = 1;
		command = _get_location(command);
	}

	if (!command || (access(command, F_OK) == -1))
	{
		if (errno == EACCES)
		{
			rem = (_create_error(args, 126));
		}
		else
		{
			rem = (_create_error(args, 127));
		}
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
			{
				free(command);
			}
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(command, args, environ);
			if (errno == EACCES)
			{
				rem = (_create_error(args, 126));
			}
			free_env();
			_free_args(args, front);
			_free_alias_list(aliases);
			_exit(rem);
		}
		else
		{
			wait(&stat);
			rem = WEXITSTATUS(stat);
		}
	}
	if (flag)
	{
		free(command);
	}
	return (rem);
}

/**
 * main - Runs a simple UNIX command interpreter
 * @argc: The number of arguments supplied to the program
 * @argv: An array oof pointers to the arguments
 *
 * Return: The return value of the last executed command
 */

int main(int argc, char *argv[])
{
	int rem = 0, retr;
	int *exe_retr = &retr;
	char *prompt = "$ ", *new_line = "\n";

	name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, _sig_handler);

	*exe_retr = 0;
	environ = _copyenv();
	if (!environ)
	{
		exit(-100);
	}

	if (argc != 1)
	{
		rem = _proc_file_commands(argv[1], exe_retr);
		free_env();
		_free_alias_list(aliases);
		return (*exe_retr);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (rem != END_OF_FILE && rem != EXIT)
		{
			rem = _handle_args(exe_retr);
		}
		free_env();
		_free_alias_list(aliases);
		return (*exe_retr);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		rem = _handle_args(exe_retr);
		if (rem == END_OF_FILE || rem == EXIT)
		{
			if (rem == END_OF_FILE)
			{
				write(STDOUT_FILENO, new_line, 1);
			}
			free_env();
			_free_alias_list(aliases);
			exit(*exe_retr);
		}
	}

	free_env();
	_free_alias_list(aliases);
	return (*exe_retr);
}
