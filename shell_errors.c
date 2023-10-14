#include "simple_shell.h"

/**
 *_eputs - Prints an input string
 * @str: The string to be printed
 *
 * Return: Nothing
 */
void e_puts(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		e_putchar(str[j]);
		j++;
	}
}


/**
 * put_fd - Writes the character c to a given file descriptor
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int put_fd(char c, int fd)
{
	static int j;
	static char buf[WRITE_BUFF_SIZE];

	if (c == BUFF_FLUSH || j >= WRITE_BUFF_SIZE)
	{
		write(fd, buf, j);
		j = 0;
	}
	if (c != BUFF_FLUSH)
		buf[j++] = c;
	return (1);
}

/**
 *puts_fd - Prints an input string
 * @str: The string to be printed
 * @fd: The file descriptor to write to
 *
 * Return: The number of chars put
 */
int puts_fd(char *str, int fd)
{
	int j = 0;

	if (!str)
		return (0);
	while (*str)
	{
		j += put_fd(*str++, fd);
	}
	return (j);
}

/**
 * e_putchar - Writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int e_putchar(char c)
{
	static int j;
	static char buf[WRITE_BUFF_SIZE];

	if (c == BUFF_FLUSH || j >= WRITE_BUFF_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}
	if (c != BUFF_FLUSH)
		buf[j++] = c;
	return (1);
}