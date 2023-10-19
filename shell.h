#ifndef _SHELL_H_
#define _SHELL_H_

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

extern char **environ;
char *name;
int hist;

/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @nxt: A pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *nxt;
} list_t;

/**
 * struct builtin_s - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @nxt: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *nxt;
} alias_t;

alias_t *aliases;

/* Main Helpers */
ssize_t _getline(char **lineptr, size_t *l, FILE *stream);
void  *re_alloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_strtok(char *line, char *delimited);
char *_get_location(char *command);
list_t *_get_path_dir(char *path);
int _execute(char **args, char **front);
void _free_list(list_t *head);
char *itoa(int num);

/* Input Helpers */
void _handle_line(char **line, ssize_t read);
void _replace_variable(char **args, int *exe_retr);
int _check_args(char **args);
int _handle_args(int *exe_retr);
char *_get_args(char *line, int *exe_retr);
int _call_args(char **args, char **front, int *exe_retr);
int _run_args(char **args, char **front, int *exe_retr);
void _free_args(char **args, char **front);
char **_replace_aliases(char **args);

/* String functions */
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
int _strlen(const char *s);
char *_strncat(char *dest, const char *src, size_t n);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strncmp(const char *s1, const char *s2, size_t n);

/* Builtins */
int (*_get_builtin(char *command))(char **args, char **front);
int _shellby_exit(char **args, char **front);
int _shellby_cd(char **args, char __attribute__((__unused__)) **front);
int _shellby_help(char **args, char __attribute__((__unused__)) **front);
int _shellby_alias(char **args, char __attribute__((__unused__)) **front);
int _shellby_env(char **args, char __attribute__((__unused__)) **front);
int _shellby_unsetenv(char **args, char __attribute__((__unused__)) **fornt);
int _shellby_setenv(char **args, char __attribute__((__unused__)) **front);

/* Builtin helpers */
void free_env(void);
char **_copyenv(void);
char **_getenv(const char *var);

/* Error handling */
int _create_error(char **args, int err);
char *_error_env(char **args);
char *_error_1(char **args);
char *_error_2_syntax(char **args);
char *_error_2_cd(char **args);
char *_error_2_exit(char **args);
char *_error_126(char **args);
char *_error_127(char **args);

/* Linkedlist helpers */
void _free_list(list_t *head);
void _free_alias_list(alias_t *head);
list_t *_add_node_end(list_t **head, char *dir);
alias_t *_add_alias_end(alias_t **head, char *name, char *value);

void _help_all(void);
void _help_alias(void);
void _help_help(void);
void _help_cd(void);
void _help_exit(void);
void _help_env(void);
void _help_unsetenv(void);
void _help_history(void);
void _help_setenv(void);

int _proc_file_commands(char *file_path, int *exe_retr);

#endif
