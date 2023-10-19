#include "shell.h"

char *_get_pid(void);
void _free_args(char **args, char **front);
char *_get_env_value(char *start, int len);
void _replace_variable(char **args, int *exe_retr);

/**
 * _get_pid - Gets the current process ID
 * Description: Opens the stat file, a space-delimited file containing
 * information about the current process. The PID is the first word in
 * the file. The function reads the PID into a buffer and replace the
 * space at the end with a \0 byte
 *
 * Return: The current process ID or NULL on failure
 */

char *_get_pid(void)
{
	ssize_t file;
	size_t indx = 0;
	char *buffer;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[indx] != ' ')
		indx++;
	buffer[indx] = '\0';

	close(file);
	return (buffer);
}

/**
 * _free_args - Frees up memory taken by args
 * @args: A null terminated double pointer containing arguments
 * @front: A double poinet to the beginning of args
 */

void _free_args(char **args, char **front)
{
	size_t indx;

	for (indx = 0; args[indx] || args[indx + 1]; indx++)
	{
		free(args[indx]);
	}
	free(front);
}

/**
 * _get_env_value - Gets the value to an environmental variable
 * @start: The environmental variable to search for
 * @len: The length of the environmental variable
 *
 * Return: If the variable is not found, an empty string
 * Otherwise, the value of the environmental variable
 *
 * Description: Variables are stored in the format VARIABLE=VALUE
 */

char *_get_env_value(char *start, int len)
{
	char **var_addy;
	char *substitute = NULL, *var, *temp;

	var = malloc(len + 1);
	if (!var)
	{
		return (NULL);
	}
	var[0] = '\0';
	_strncat(var, start, len);

	var_addy = _getenv(var);
	free(var);
	if (var_addy)
	{
		temp = *var_addy;
		while (*temp != '=')
			temp++;

		temp++;
		substitute = malloc(_strlen(temp) + 1);
		if (substitute)
			_strcpy(substitute, temp);
	}

	return (substitute);
}

/**
 * _replace_variable - Handles variable replacement
 * @line: A double pointer containing the command and arguments
 * @exe_retr: A pointer to the return value of the last executed
 * command
 *
 * Description: Replaces $$ with the current PID, $? with the return
 * value of the last executed program, and environmental variables
 * proceeded by $ with their corresponding value
 */

void _replace_variable(char **line, int *exe_retr)
{
	int m, n = 0, length;
	char *substitute = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (m = 0; old_line[m]; m++)
	{
		if (old_line[m] == '$' && old_line[m + 1] &&
				old_line[m + 1] != ' ')
		{
			if (old_line[m + 1] == '$')
			{
				substitute = _get_pid();
				n = m + 2;
			}
			else if (old_line[m + 1] == '?')
			{
				substitute = itoa(*exe_retr);
				n = m + 2;
			}
			else if (old_line[m + 1])
			{
				for (n = m + 1; old_line[n] &&
						old_line[n] != '$' &&
						old_line[n] != ' '; n++)
					;
				length = n - (m + 1);
				substitute = _get_env_value(&old_line[m + 1], length);
			}
			new_line = malloc(m + _strlen(substitute)
					+ _strlen(&old_line[n]) + 1);
			if (!line)
			{
				return;
			}
			new_line[0] = '\0';
			_strncat(new_line, old_line, m);
			if (substitute)
			{
				_strcat(new_line, substitute);
				free(substitute);
				substitute = NULL;
			}
			_strcat(new_line, &old_line[n]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			m = -1;
		}
	}
}
