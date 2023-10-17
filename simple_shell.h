#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>

/* macros for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* for reading and writing buffers */
#define READ_BUFF_SIZE 1024
#define WRITE_BUFF_SIZE 1024
#define BUFF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr - Singly linked list
 * @num: The number field
 * @str: A pointer to a string
 * @next: Points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - Contains pseudo-arguements to pass to a function,
 *		which will allow uniform prototype for function pointer struct
 *@arg: A pointer string generated from getline containing arguements
 *@argv: An array of strings generated from arg
 *@path: A pointer string path for the current command
 *@argc: The number of arguements
 *@line_count: The error count
 *@environ: custom modified copy of environ from LL env
 *@err_num: The error code for exit()s
 *@linecount_flag: If on count this line of input
 *@fname: The program filename
 *@env: Linked list local copy of environ
 *@history: The history node
 *@alias: The alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	char **environ;
	int env_changed;
	int status;
	list_t *env;
	list_t *history;
	list_t *alias;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - Contains a builtin string and related function
 *@type: The builtin command flag
 *@func: The function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* my_shell_string.c */
int _str_len(char *);
int _str_cmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* my_shell_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* shell_errors.c */
void e_puts(char *);
int e_putchar(char);
int put_fd(char c, int fd);
int puts_fd(char *str, int fd);

/* shell_errors1.c */
int err_atoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* shell_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t _print_list_str(const list_t *);
int _delete_node_at_index(list_t **, unsigned int);
void _free_list(list_t **);

/* shell_lists1.c */
size_t _list_len(const list_t *);
char **list_to_strings(list_t *);
size_t _print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t _get_node_index(list_t *, list_t *);

/* shell_vars.c */
int _is_chain(info_t *, char *, size_t *);
void _check_chain(info_t *, char *, size_t *, size_t, size_t);
int _replace_alias(info_t *);
int _replace_vars(info_t *);
int _replace_string(char **, char *);


#endif
