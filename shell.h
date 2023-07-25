#ifndef _SHELL_H_
#define _SHELL_H_

#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>



#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1


#define CMD_NORM    0
#define CMD_OR      1
#define CMD_AND     2
#define CMD_CHAIN   3


#define CONVERT_LOWERCASE   1
#define CONVERT_UNSIGNED    2


#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE   ".simple_shell_history"
#define HIST_MAX    4096

extern char **environ;


/**
 * struct liststr - lnk lst
 * @num: num field
 * @str: str
 * @next: nxt node
 */
typedef struct liststr
{
    int num;
    char *str;
    struct liststr *next;
} list_t;

/**
 * struct passinfo - arguements to send to function.
 * @arg: str generated from getline.
 * @argv:an arr of strings.
 * @path: str path for command
 * @argc: arg num
 * @line_count: err numb
 * @err_num: err code
 * @linecount_flag: on count
 * @fname: prog name
 * @env: local copy
 * @environ: modi copy of environ
 * @history: hist node
 * @alias: id node
 * @env_changed: env change
 * @status: return stat
 * @cmd_buf: address of ptr
 * @cmd_buf_type: buff type
 * @readfd: read line input
 * @histcount: hist of num count
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
    list_t *env;
    list_t *history;
    list_t *alias;
    char **environ;
    int env_changed;
    int status;

    char **cmd_buf;
    int cmd_buf_type;
    int readfd;
    int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
        0, 0, 0}

/**
 * struct builtin - builtin string
 * @type: com flag
 * @func: func
 */
typedef struct builtin
{
    char *type;
    int (*func)(info_t *);
} builtin_table;


int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

 
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);
 
int loophsh(char **);

int _putsfd(char *str, int fd);
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
 
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
int _strlen(char *);
int _strcmp(char *, char *);

char *_strcpy(char *, char *);
void _puts(char *);
int _putchar(char);
char *_strdup(const char *);

void *_realloc(void *, unsigned int, unsigned int);
char *_memset(char *, char, unsigned int);
void ffree(char **);

void print_error(info_t *, char *);
char *convert_number(long int, int, int);
void remove_comments(char *);
int _erratoi(char *);
int print_d(int, int);
 
int _myexit(info_t *);
int _myhelp(info_t *);
int _mycd(info_t *);

int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int bfree(void **);
int _atoi(char *);

int _myhistory(info_t *);
int _myalias(info_t *);

ssize_t get_input(info_t *);
void sigintHandler(int);

int _getline(info_t *, char **, size_t *);

void clear_info(info_t *);
void free_info(info_t *, int);
void set_info(info_t *, char **);

char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);

int _myunsetenv(info_t *);
int populate_env_list(info_t *);

char **get_environ(info_t *);
int _setenv(info_t *, char *, char *);
int _unsetenv(info_t *, char *);

char *_strchr(char *, char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);

char **strtow(char *, char *);
char **strtow2(char *, char);

char *get_history_file(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);

int replace_string(char **, char *);
int is_chain(info_t *, char *, size_t *);
int replace_vars(info_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);

size_t list_len(const list_t *);
char **list_to_strings(list_t *);
ssize_t get_node_index(list_t *, list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);

size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
void free_list(list_t **);

#endif
