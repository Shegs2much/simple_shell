#include "shell.h"

char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
int _strlen(const char *s);
char *_strncat(char *dest, const char *src, size_t n);

/**
 * _strcpy - Copies the string pointed to by src, including the
 * terminating null byte, to the buffer pointed by dest
 * @dest: Pointer to the destination of copied string
 * @src: Pointer to the src of the source string
 *
 * Return: Pointer to dest
 */

char *_strcpy(char *dest, const char *src)
{
	size_t indx;

	for (indx = 0; src[indx] != '\0'; indx++)
	{
		dest[indx] = src[indx];
	}
	dest[indx] = '\0';
	return (dest);
}

/**
 * _strcat - Concatenates two strings
 * @dest: Pointer to destination string
 * @src: Pointer to source string
 *
 * Return: Pointer to destination string
 */

char *_strcat(char *dest, const char *src)
{
	char *destTmp;
	const char *srcTmp;

	destTmp =  dest;
	srcTmp = src;

	while (*destTmp != '\0')
	{
		destTmp++;
	}

	while (*srcTmp != '\0')
	{
		*destTmp++ = *srcTmp++;
	}
	*destTmp = '\0';
	return (dest);
}

/**
 * _strlen - Returns the length of a string
 * @s: A pointer to the character string
 *
 * Return: The length of the string
 */

int _strlen(const char *s)
{
	int length;

	length = 0;

	if (!s)
	{
		return (length);
	}
	for (length = 0; s[length]; length++)
	{
		;
	}
	return (length);
}

/**
 * _strncat - Concatenates two strings where n number of
 * bytes are copied from source
 * @dest: Pointer to destination string
 * @src: Pointer to source string
 * @n: n bytes to copy from src
 *
 * Return: Pointer to destination string
 */

char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_length = _strlen(dest);
	size_t indx;

	for (indx = 0; indx < n && src[indx] != '\0'; indx++)
	{
		dest[dest_length + indx] = src[indx];
	}
	dest[dest_length + indx] = '\0';

	return (dest);
}
