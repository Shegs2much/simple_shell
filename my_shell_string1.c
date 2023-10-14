#include "simple_shell.h"

/**
 * _strcpy - Copies a string
 * @dest: The destination of the string
 * @src: The source of the string
 *
 * Return: Pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int j = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[j])
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = 0;
	return (dest);
}

/**
 *_puts - Prints an input string
 *@str: The string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_putchar(str[j]);
		j++;
	}
}

/**
 * _putchar - Writes the character c to stdout(standare output)
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int j;
	static char buf[WRITE_BUFF_SIZE];

	if (c == BUFF_FLUSH || j >= WRITE_BUFF_SIZE)
	{
		write(1, buf, j);
		j = 0;
	}
	if (c != BUFF_FLUSH)
		buf[j++] = c;
	return (1);
}

/**
 * _strdup - Duplicates a string
 * @str: String to duplicate
 *
 * Return: Pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (len++; len--;)
		ret[len] = *--str;
	return (ret);
}