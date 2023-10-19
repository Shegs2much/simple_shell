#include "shell.h"

ssize_t _get_new_length(char *line);
void _handle_line(char **line, ssize_t read);
void _logical_op(char *line, ssize_t *new_len);

/**
 * _get_new_length - Gets the new length of a line
 * partitioned by ";", "||", "&&&", or "#"
 * @line: The line to check
 *
 * Return: The new length of the line
 *
 * Description: Cuts short lines containing '#' comments with '\0'
 */

ssize_t _get_new_length(char *line)
{
	size_t indx;
	ssize_t new_len = 0;
	char current, nxt;

	for (indx = 0; line[indx]; indx++)
	{
		current = line[indx];
		nxt = line[indx + 1];
		if (current == '#')
		{
			if (indx == 0 || line[indx - 1] == ' ')
			{
				line[indx] = '\0';
				break;
			}
		}
		else if (indx != 0)
		{
			if (current == ';')
			{
				if (nxt == ';' && line[indx - 1] != ' ' && line[indx - 1] != ';')
				{
					new_len += 2;
					continue;
				}
				else if (line[indx - 1] == ';' && nxt != ' ')
				{
					new_len += 2;
					continue;
				}
				if (line[indx - 1] != ' ')
					new_len++;
				if (nxt != ' ')
					new_len++;
			}
			else
			{
				_logical_op(&line[indx], &new_len);
			}
		}
		else if (current == ';')
		{
			if (indx != 0 && line[indx - 1] != ' ')
				new_len++;
			if (nxt != ' ' && nxt != ';')
				new_len++;
		}
		new_len++;
	}
	return (new_len);
}

/**
 * _handle_line - Partitions a line read from standard input
 * @line: A pointer to the line read fron standard input
 * @read: The length of the line
 *
 * Description: Spaces are inserted to separate ";", "||", and "&&"
 * Replaces "#" with '\0'
 */

void _handle_line(char **line, ssize_t read)
{
	size_t indx, m;
	ssize_t new_len;
	char prev, curr, nxt;
	char *old_line, *new_line;

	new_len = _get_new_length(*line);
	if (new_len == read - 1)
	{
		return;
	}
	new_line = malloc(new_len + 1);
	if (!new_line)
	{
		return;
	}
	m = 0;
	old_line = *line;
	for (indx = 0; old_line[indx]; indx++)
	{
		curr = old_line[indx];
		nxt = old_line[indx + 1];
		if (indx != 0)
		{
			prev = old_line[indx - 1];
			if (curr == ';')
			{
				if (nxt == ';' && prev != ' ' && prev != ';')
				{
					new_line[m++] = ' ';
					new_line[m++] = ';';
					continue;
				}
				else if (prev == ';' && nxt != ' ')
				{
					new_line[m++] = ';';
					new_line[m++] = ' ';
					continue;
				}
				if (prev != ' ')
				{
					new_line[m++] = ' ';
				}
				new_line[m++] = ';';
				if (nxt != ' ')
				{
					new_line[m++] = ' ';
				}
				continue;
			}
			else if (curr == '&')
			{
				if (nxt == '&' && prev != ' ')
				{
					new_line[m++] = ' ';
				}
				else if (prev == '&' && nxt != ' ')
				{
					new_line[m++] = '&';
					new_line[m++] = ' ';
					continue;
				}
			}
			else if (curr == '|')
			{
				if (nxt == '|' && prev != ' ')
				{
					new_line[m++] = ' ';
				}
				else if (prev == '|' && nxt != ' ')
				{
					new_line[m++] = '|';
					new_line[m++] = ' ';
					continue;
				}
			}
		}
		else if (curr == ';')
		{
			if (indx != 0 && old_line[indx - 1] != ' ')
			{
				new_line[m++] = ' ';
			}
			new_line[m++] = ';';
			if (nxt != ' ' && nxt != ';')
			{
				new_line[m++] = ' ';
			}
			continue;
		}
		new_line[m++] = old_line[indx];
	}
	new_line[m] = '\0';

	free(*line);
	*line =  new_line;
}

/**
 * _logical_op - Checks a line for logical operators "||" or "&&"
 * @line: A pointer to the character to check in the line
 * @new_len: Pointer to new_len in _get_new_length function
 */

void _logical_op(char *line, ssize_t *new_len)
{
	char prev, curr, nxt;

	prev = *(line - 1);
	curr = *line;
	nxt = *(line + 1);

	if (curr == '&')
	{
		if (nxt == '&' && prev != ' ')
		{
			(*new_len)++;
		}
		else if (prev == '&' && nxt != ' ')
		{
			(*new_len)++;
		}
	}
	else if (curr == '|')
	{
		if (nxt == '|' && prev != ' ')
		{
			(*new_len)++;
		}
		else if (prev == '|' && nxt != ' ')
		{
			(*new_len)++;
		}
	}
}
