#include "shell.h"

int _num_length(int num);
char *itoa(int num);
int _create_error(char **args, int err);

/**
 * _num_length - Counts the digit length of a number
 * @num: The number to measure
 *
 * Return: The digit's length
 */

int _num_length(int num)
{
	int length = 1;
	unsigned int num1;

	if (num < 0)
	{
		length++;
		num1 = num * -1;
	}
	else
	{
		num1 = num;
	}
	while (num1 > 9)
	{
		length++;
		num1 /= 10;
	}

	return (length);
}

/**
 * itoa - Converts an integer to a string
 * @num: The integer to be converted
 *
 * Return: The converted string
 */
char *itoa(int num)
{
	int length = _num_length(num);
	unsigned int num1;
	char *buffer;

	buffer = malloc(sizeof(char) * (length + 1));
	if (!buffer)
	{
		return (NULL);
	}

	buffer[length] = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = num;
	}

	length--;
	do {
		buffer[length] = (num1 % 10) + '0';
		num1 /= 10;
		length--;
	} while (num1 > 0);

	return (buffer);
}

/**
 * _create_error - Writes a custom error message to stderr
 * @args: Array of arguments
 * @err: The error value
 *
 * Return: The error value
 */

int _create_error(char **args, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = _error_env(args);
		break;
	case 1:
		error = _error_1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
		{
			error = _error_2_exit(++args);
		}
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
		{
			error = _error_2_syntax(args);
		}
		else
		{
			error = _error_2_cd(args);
		}
		break;
	case 126:
		error = _error_126(args);
		break;
	case 127:
		error = _error_127(args);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
	{
		free(error);
	}
	return (err);
}
