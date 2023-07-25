#ifndef _SHELL_H_
#define _SHELL_H_

#include <limits.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>


#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define USE_GETLINE 0
#define USE_STRTOK 0

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

/**
 * struct liststr - list string function struct
 * @num: num
 * @str: strings
 * @next: points
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains some args
 * @arg: str
 * @argv:an arr
 * @path: str loc
 * @argc: arg
 * @cmd_buf_type: command
 * @readfd: fd
 * @histcount: hist
 * @env_changed: checks env change
 * @status: status
 * @cmd_buf: location
 * @line_count: err num
 * @err_num: err code
 * @linecount_flag: on count
 * @fname: the program file name
 * @env: lnk list
 * @environ: copy mod
 * @history: hist node
 * @alias: alias node
 * @env_changed: on if env change
 */

typedef struct passinfo
{
	list_t *env;
	list_t *history;
	list_t *alias;
	char *arg;
	char **argv;
	char *path;
	char *fname;
	char **environ;
	char **cmd_buf;
	int env_changed;
	int status;
	int readfd;
	int histcount;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	int argc;
	int cmd_buf_type;


} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - built in str
 * @type: built in type
 * @func: functi
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int loophsh(char **);

int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);
int find_builtin(info_t *);
void find_cmd(info_t *);
int hsh(info_t *, char **);
void fork_cmd(info_t *);


char *_memset(char *, char, unsigned int);
void *_realloc(void *, unsigned int, unsigned int);
void ffree(char **);
int bfree(void **);


char **strtow(char *, char *);
char **strtow2(char *, char);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

void _puts(char *);
int _putchar(char);
char *_strcpy(char *, char *);
char *_strdup(const char *);

char *_getenv(info_t *, const char *);
int _myenv(info_t *);

void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

int _myhistory(info_t *);
int _myalias(info_t *);
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

int interactive(info_t *);
int _isalpha(int);
int _atoi(char *);
int is_delim(char, char *);


int is_chain(info_t *, char *, size_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);

size_t list_len(const list_t *);
char **list_to_strings(list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
size_t print_list(const list_t *);

list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

char *get_history_file(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);

int _unsetenv(info_t *, char *);
char **get_environ(info_t *);
int _setenv(info_t *, char *, char *);

int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);
#endif
