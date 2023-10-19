#include "shell.h"

char **_strtok(char *line, char *delimited);
int _count_tokens(char *str, char *delimited);
int _token_length(char *str, char *delimited);

/**
 * _strtok - Tokenizes a string
 * @line: The string to be tokenized
 * @delimited: The delimeter character to tokenize the string by
 *
 * Return: A pointer to an array containing the tokenized words
 */

char **_strtok(char *line, char *delimited)
{
	char **ptr;
	int indx = 0, tokens, tt, letters, ll;

	tokens = _count_tokens(line, delimited);
	if (tokens == 0)
	{
		return (NULL);
	}

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
	{
		return (NULL);
	}

	for (tt = 0; tt < tokens; tt++)
	{
		while (line[indx] == *delimited)
		{
			indx++;
		}

		letters = _token_length(line + indx, delimited);

		ptr[tt] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[tt])
		{
			for (indx -= 1; indx >= 0; indx--)
			{
				free(ptr[indx]);
			}
			free(ptr);
			return (NULL);
		}

		for (ll = 0; ll < letters; ll++)
		{
			ptr[tt][ll] = line[indx];
			indx++;
		}

		ptr[tt][ll] = '\0';
	}
	ptr[tt] = NULL;
	ptr[tt + 1] = NULL;

	return (ptr);
}

/**
 * _count_tokens - Counts the number of delmited words contained
 * within a string
 * @str: The string to be searched
 * @delimited: The delimited character
 *
 * Return: The number of words conntained within str
 */

int _count_tokens(char *str, char *delimited)
{
	int indx, tokens = 0, length = 0;

	for (indx = 0; *(str + indx); indx++)
	{
		length++;
	}

	for (indx = 0; indx < length; indx++)
	{
		if (*(str + indx) != *delimited)
		{
			tokens++;
			indx += _token_length(str + indx, delimited);
		}
	}

	return (tokens);
}

/**
 * _token_length - Locates the delimiter index marking the end of the
 * first token contained within a string
 * @str: The string to be searched
 * @delimited: The delimited character
 *
 * Return: The delimited index marking the end of the initial token
 * pointed to the str
 */

int _token_length(char *str, char *delimited)
{
	int indx = 0, length = 0;

	while (*(str + indx) && *(str + indx) != *delimited)
	{
		length++;
		indx++;
	}

	return (length);
}
