#include "shell.h"

int _cant_open(char *file_path);
int _proc_file_commands(char *file_path, int *exe_retr);

/**
 * _cant_open - If the file doesn't exist or lacks proper permissions,
 * print a can't open error
 * @file_path: Path to the supposed file
 *
 * Return: 127
 */

int _cant_open(char *file_path)
{
	char *error, *history_str;
	int length;

	history_str = itoa(hist);
	if (!history_str)
	{
		return (127);
	}

	length = _strlen(name) + _strlen(history_str) + _strlen(file_path) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(history_str);
		return (127);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, history_str);
	_strcat(error, ": Can't open ");
	_strcat(error, file_path);
	_strcat(error, "\n");

	free(history_str);
	write(STDERR_FILENO, error, length);
	free(error);
	return (127);
}

/**
 * _proc_file_commands - Takes a file and attempts to run the command stored
 * within
 * @file_path: Path to the file
 * @exe_retr: Return value of the last executed command
 *
 * Return: If file couldn't be opened - 127
 * If malloc fails - -1
 * Otherwise the return value of the last command ran
 */

int _proc_file_commands(char *file_path, int *exe_retr)
{
	int rem;
	char buffer[120];
	char *line, **args, **front;
	unsigned int line_size = 0;
	unsigned int old_size = 120;
	ssize_t file, bb_read, indx;

	hist = 0;
	file = open(file_path, O_RDONLY);
	
	if (file == -1)
	{
		*exe_retr = _cant_open(file_path);
		return (*exe_retr);
	}
	line = malloc(sizeof(char) * old_size);
	if (!line)
	{
		return (-1);
	}
	do {
		bb_read = read(file, buffer, 119);
		if (bb_read == 0 && line_size == 0)
		{
			return (*exe_retr);
		}
		buffer[bb_read] = '\0';
		line_size += bb_read;
		line = re_alloc(line, old_size, line_size);
		_strcat(line, buffer);
		old_size = line_size;
	} while (bb_read);
	for (indx = 0; line[indx] == '\n'; indx++)
	{
		line[indx] = ' ';
	}
	for (; indx < line_size; indx++)
	{
		if (line[indx] == '\n')
		{
			line[indx] = ';';
			for (indx += 1; indx < line_size && line[indx] == '\n'; indx++)
			{
				line[indx] = ' ';
			}
		}
	}
	_replace_variable(&line, exe_retr);
	_handle_line(&line, line_size);
	args = _strtok(line, " ");
	free(line);
	if (!args)
	{
		return (0);
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

	rem = _call_args(args, front, exe_retr);

	free(front);
	return (rem);
}
