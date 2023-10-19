#include "shell.h"

void  *re_alloc(void *ptr, unsigned int old_size, unsigned int new_size);
void _assign_lineptr(char **lineptr, size_t *l, char *buffer, size_t b);
ssize_t _getline(char **lineptr, size_t *l, FILE *stream);

/**
 * re_alloc - Reallocates a memory block using malloc and free
 * @ptr: Pointer to the memory previously allocated
 * @old_size: The size of allocated space for ptr in bytes
 * @new_size: The size of the new memory block in bytes
 */

void *re_alloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	unsigned int indx;
	void *mem;
	char *ptr_dup, *fill;

	if (new_size == old_size)
	{
		return (ptr);
	}

	if (ptr == NULL)
	{
		mem = malloc(new_size);
		if (mem == NULL)
		{
			return (NULL);
		}

		return (mem);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	ptr_dup = ptr;
	mem = malloc(sizeof(*ptr_dup) * new_size);
	if (mem == NULL)
	{
		free(ptr);
		return (NULL);
	}

	fill = mem;

	for (indx = 0; indx < old_size && indx < new_size; indx++)
	{
		fill[indx] = *ptr_dup++;
	}

	free(ptr);
	return (mem);
}

/**
 * _assign_lineptr - Reassigns the lineptr variable for _getline
 * @lineptr: Buffer to store an input string
 * @l: The size of lineptr
 * @buffer: The string to assign to lineptr
 * @b: The size of buffer
 */

void _assign_lineptr(char **lineptr, size_t *l, char *buffer, size_t b)
{
	if (*lineptr == NULL)
	{
		if (b > 120)
		{
			*l = b;
		}
		else
		{
			*l = 120;
		}
		*lineptr = buffer;
	}
	else if (*l < b)
	{
		if (b > 120)
		{
			*l = b;
		}
		else
		{
			*l = 120;
		}
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * _getline - Reads input from a stream
 * @lineptr: A buffer to store an input
 * @l: The size of lineptr
 * @stream: The stream to read from
 *
 * Return: The number of bytes read
 */

ssize_t _getline(char **lineptr, size_t *l, FILE *stream)
{
	static ssize_t input;
	ssize_t rem;
	char c = 'x', *buffer;
	int f;

	if (input == 0)
	{
		fflush(stream);
	}
	else
	{
		return (-1);
	}
	input = 0;

	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
	{
		return (-1);
	}

	while (c != '\n')
	{
		f = read(STDIN_FILENO, &c, 1);
		if (f == 1 || (f == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (f == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 120)
		{
			buffer = re_alloc(buffer, input, input + 1);
		}

		buffer[input] = c;
		input++;
	}
	buffer[input] = '\0';

	_assign_lineptr(lineptr, l, buffer, input);

	rem = input;
	if (f != 0)
	{
		input = 0;
	}
	return (rem);
}
