#include "shell.h"

int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strncmp(const char *s1, const char *s2, size_t n);

/**
 * _strcmp - Compares two strings
 * @s1: The first string to be compared
 * @s2: The second string to be compared
 *
 * Return: Positive byte difference if s1 > s2
 * 0 if s1 = s2
 * Negative byte difference if s1 < s2
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 != *s2)
	{
		return (*s1 - *s2);
	}

	return (0);
}

/**
 * _strchr - Locates a character in a string
 * @s: The string to be searched
 * @c: The character to be located
 *
 * Return: If c is found - a pointer to the first occurence
 * If c is not found - NULL
 */

char *_strchr(char *s, char c)
{
	int indx;

	for (indx = 0; s[indx]; indx++)
	{
		if (s[indx] == c)
		{
			return (s + indx);
		}
	}

	return (NULL);
}

/**
 * _strspn - Gets the length of a prefix substring
 * @s: The string to be searched
 * @accept: The prefix to be measured
 *
 * Return: The number of bytes in s which consist only of
 * bytes from accept
 */

int _strspn(char *s, char *accept)
{
	int bytes = 0;
	int indx;

	while (*s)
	{
		for (indx = 0; accept[indx]; indx)
		{
			if (*s == accept[indx])
			{
				bytes++;
				break;
			}
		}
		s++;
	}
	return (bytes);
}

/**
 * _strncmp - Compares two strings
 * @s1: Pointer to the first string
 * @s2: Pointer to the second string
 * @n: The first n bytes of the strings to compare
 *
 * Return: Less than 0 if s1 is shorter than s2
 * 0 if s1 and s2 match
 * Greater than 0 if s1 is longer than s2
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t indx;

	for (indx = 0; s1[indx] && s2[indx] && indx < n; indx++)
	{
		if (s1[indx] > s2[indx])
		{
			return (s1[indx] - s2[indx]);
		}
		else if (s1[indx] - s2[indx])
		{
			return (s1[indx] - s2[indx]);
		}
	}
	if (indx == n)
	{
		return (0);
	}
	else
	{
		return (-15);
	}
}
