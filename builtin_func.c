#include "shell.h"
int (*_get_builtin(char *command))(char **args, char **front);
int _shellby_exit(char **args, char **front);
int _shellby_cd(char **args, char __attribute__((__unused__)) **front);
int _shellby_help(char **args, char __attribute__((__unused__)) **front);

/**
 * _get_builtin - Matches a command with a corresponding
 *	shellby builtin function
 * @command: The command to match
 *
 * Return: A function pointer to the corresponding builtin
 */

int (*_get_builtin(char *command))(char **args, char **front)
{
	builtin_t funcs[] = {
		{ "exit", _shellby_exit },
		{ "env", _shellby_env },
		{ "setenv", _shellby_setenv },
		{ "unsetenv", _shellby_unsetenv },
		{ "cd", _shellby_cd },
		{ "alias", _shellby_alias },
		{ "help", _shellby_help },
		{ NULL, NULL}
	};
	int indx;

	for (indx = 0; funcs[indx].name; indx++)
	{
		if (_strcmp(funcs[indx].name, command) == 0)
			break;
	}
	return (funcs[indx].f);
}

/**
 * _shellby_exit - Causes normal process termination
 *	for the shellby shell.
 * @args: An array of arguments cointaining the exit value
 * @front: A double pointer to the beginning of args
 *
 * Return: If there are no arguments - -3.
 *	If the given exit value is invalid - 2.
 *	0/w - exits with the given status value.
 *
 * Description: Upon returning -3, the program exits back in the main function
 */

int _shellby_exit(char **args, char **front)
{
	int indx, length_of_int = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			indx = 1;
			length_of_int++;
		}
		for (; args[0][indx]; indx++)
		{
			if (indx <= length_of_int && args[0][indx] >= '0' && args[0][indx] <= '9')
				num = (num * 10) + (args[0][indx] - '0');
			else
				return (_create_error(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (_create_error(--args, 2));
	args -= 1;
	_free_args(args, front);
	free_env();
	_free_alias_list(aliases);
	exit(num);
}

/**
 * _shellby_cd - Changes the current directory of the shellby process
 * @args: An array of arguments
 * @front: A double pointer to the beginning of args
 *
 * Return: If the given string is not a directory - 2.
 *	If an error occurs - -1
 *	Otherwise - 0
 */

int _shellby_cd(char **args, char __attribute__((__unused__)) **front)
{
	char **dir_info, *new_line = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '_' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
					(chdir(*_getenv("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (_create_error(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(oldpwd);
				return (_create_error(args, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			chdir(*(_getenv("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "OLDPWD";
	dir_info[1] = oldpwd;
	if (_shellby_setenv(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (_shellby_setenv(dir_info, dir_info) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(oldpwd);
	free(pwd);
	free(dir_info);
	return (0);
}

/**
 * _shellby_help - Displays information about shellny bultin commands
 * @args: An array of arguments
 * @front: A pointer to the beginning of args
 *
 * Return: If an error occurs - -1
 *	Otherwise - 0
 */

int _shellby_help(char **args, char __attribute__((__unused__)) **front)
{
	if (!args[0])
		_help_all();
	else if (_strcmp(args[0], "alias") == 0)
		_help_alias();
	else if (_strcmp(args[0], "cd") == 0)
		_help_cd();
	else if (_strcmp(args[0], "exit") == 0)
		_help_exit();
	else if (_strcmp(args[0], "env") == 0)
		_help_env();
	else if (_strcmp(args[0], "setenv") == 0)
		_help_setenv();
	else if (_strcmp(args[0], "unsetenv") == 0)
		_help_unsetenv();
	else if (_strcmp(args[0], "help") == 0)
		_help_help();
	else
		write(STDERR_FILENO, name, _strlen(name));

	return (0);
}
