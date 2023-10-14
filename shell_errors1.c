#include "simple_shell.h"

/**
 * err_atoi - Converts a string to an integer
 * @s: Poiner to the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int err_atoi(char *s)
{
	int j = 0;
	unsigned long int res = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (j = 0;  s[j] != '\0'; j++)
	{
		if (s[j] >= '0' && s[j] <= '9')
		{
			res *= 10;
			res += (s[j] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}


/**
 * print_d - Function prints a decimal (integer) number (base 10)
 * @input: The input
 * @fd: The file descriptor to write to
 *
 * Return: The number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int j, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = e_putchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__putchar('0' + current / j);
			count++;
		}
		current %= j;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * print_error - Prints an error message
 * @info: The parameter & return info struct
 * @estr: String containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(info_t *info, char *estr)
{
	e_puts(info->fname);
	e_puts(": ");
	print_d(info->line_count, STDERR_FILENO);
	e_puts(": ");
	e_puts(info->argv[0]);
	e_puts(": ");
	e_puts(estr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}

/**
 * convert_number - Converter function
 * @num: Number
 * @base: Base
 * @flags: Flags
 *
 * Return: String
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}