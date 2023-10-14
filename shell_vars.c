#include "simple_shell.h"

/**
 * _is_chain - Test if current char in buffer is a chain delimeter
 * @info: The parameter struct
 * @buf: The char buffer
 * @p: Address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int _is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * _check_chain - Checks if we should continue chaining based on last status
 * @info: The parameter struct
 * @buf: The char buffer
 * @p: Address of the current position in buf
 * @i: Starting position in buf
 * @len: Length of buf
 *
 * Return: Void
 */
void _check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}


/**
 * _replace_vars - Replaces vars in the tokenized string
 * @info: The parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int _replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_str_cmp(info->argv[i], "$?"))
		{
			_replace_string(&(info->argv[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_str_cmp(info->argv[i], "$$"))
		{
			_replace_string(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			_replace_string(&(info->argv[i]),
				_strdup(_str_chr(node->str, '=') + 1));
			continue;
		}
		_replace_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * _replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int _replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _str_chr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * _replace_string - Replaces string
 * @old: Address of the old string
 * @new: Address of the new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int _replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}