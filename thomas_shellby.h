#ifndef THOMAS_SHELLBY_H
#define THOMAS_SHELLBY_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024
#define TOKEN_BUFFER_SIZE 128
#define DELIMITER " \t\r\n\a"

/* This variable is declared to point to an array of strings called the environment */
extern char **environment;


/**
 * struct shellby_data – struct data type that contains all relevant data on the session
 * @argument_vect: argument vector used in session
 * @user_input: commands written in CLI
 * @arguments: various tokens in the command
 * @last_status: last status of shellby
 * @count: counts how many lines r arguentts re present
 * @_environment: defined variable of the environment
 * @shellby_pid: process ID of current shellby session
 */
typedef struct shellby_data
{
	char **argument_vect;
	char *user_input;
	char **arguments;
	int last_status;
	int count;
	char **_environment;
	char *shellby_pid;
} data_in_shellby;

/**
 * struct separator_list_single - singly linked list for separators used
 * @separator: ; | &
 * @nextn: next node
 * Description: A single linked list created to store our Shellby separators
 */
typedef struct separators_list_single
{
	char separator;
	struct separators_list_single *nextn;
} separators_list;

/**
 * struct command_line_list_single is a single linked list created to hold commands
 * @command_line: all commands in a line
 * @nextn: next node
 * Description: A single linked list created to store our Shellby command lines inputed by the user
 */
typedef struct command_line_list_single
{
	char *command_line;
	struct command_line_list_single *nextn;
} command_line_list;

/**
 * struct r_variable_list – A single linked list created to store variables
 * @length_of_variable: length of the variable
 * @variable_value: value of the variable
 * @length_of_variable_value: length of the value
 * @nextn: next node
 * Description: A single linked list created to store all our Shellby variables
 */
typedef struct r_variable_list
{
	int length_of_variable;
	char *variable_value;
	int length_of_variable_value;
	struct r_variable_list *nextn;
} r_variable;

/**
 * struct builtin_structure - Builtin structure used for all previously known command arguments.
 * @known_name: The worldwide known name of the various commands built in i.e cd, exit, env
 * @dtp_function: data type pointer function.
 */
typedef struct builtin_structure
{
	char *known_name;
	int (*dtp_function)(data_in_shellby *shellby_data_store);
} builtin_t;

/* auxillary_lists.c */
separators_list *add_separators_node_end(separators_list **header, char separators);
void free_separators_list(separators_list **header);
command_line_list *add_command_line_node_end(command_line_list **header, char *command_line);
void free_command_line_list(command_line_list **header);

/* auxillary_lists2.c */
r_variable *add_rvariable_node(r_variable **header, int length_of_var, char *variable, int length_of_val);
void free_rvariable_list(r_variable **header);

/* auxilarry_string functions */
char *_strcat(char *destination, const char *string_rc);
char *_strcpy(char *destination, char *string_rc);
int _strcmp(char *string1, char *string2);
char *_strchr(char *shellby_string, char c);
int _strspn(char *shellby_string, char *accepted);

/* auxillary_memory.c */
void _memcpy(void *current_shellby_ptr, const void *shellby_tr, unsigned int size);
void *_realloc(void *shellby_tr, unsigned int previous_size, unsigned int current_size);
char **_reallocdp(char **shellby_tr, unsigned int previous_size, unsigned int current_size);

/* auxillary_str2.c */
char *_strdup(const char *shellby_string);
int _strlen(const char *shellby_string);
int cmp_chars(char stringy[], const char *delimiter);
char *_strtok(char stringy[], const char *delimiter);
int _isdigit(const char *shellby_string);

/* auxillary_str3.c */
void rev_string(char *shellby_string);

/* check_syntax_error.c */
int repeated_char(char *user_input, int i);
int error_separators_op(char *user_input, int i, char last);
int first_char(char *user_input, int *i);
void print_syntax_error(data_in_shellby *shellby_data_store, char *user_input, int i, int bool);
int check_syntax_error(data_in_shellby *shellby_data_store, char *user_input);

/* shell_loop.c */
char *without_user_input(char *user_in);
void shell_loop(data_in_shellby *shellby_data_store);

/* read_command_line.c */
char *read_command_line(int *i_eof);

/* split.c */
char *swap_char(char *user_input, int bool);
void add_nodes(separators_list **header_separators, command_line_list **header_length, char *user_input);
void go_nextn(separators_list **list_separators, command_line_list **list_length, data_in_shellby *shellby_data_store);
int split_commands(data_in_shellby *shellby_data_store, char *user_input);
char **split_command_line(char *user_input);

/* rep_variable.c */
void check_environment(r_variable **head, char *user_in, data_in_shellby *shellby_data);
int check_vars(r_variable **head, char *user_in, char *st, data_in_shellby *shellby_data);
char *replaced_user_input(r_variable **header, char *user_input, char *current_user_input, int n_length);
char *rep_variable(char *user_input, data_in_shellby *shellby_data_store);

/* get_command_line.c */
void bring_command_line(char **command_line_ptr, size_t *n, char *shellby_buffer, size_t j);
ssize_t get_command_line(char **command_line_ptr, size_t *n, FILE *stream);

/* execute_command_line */
int execute_command_line(data_in_shellby *shellby_data_store);

/* command_execute.c */
int is_cdir(char *path, int *i);
char *_which(char *command, char **_environment);
int is_executable(data_in_shellby *shellby_data_store);
int check_error_command(char *dir, data_in_shellby *shellby_data_store);
int command_execute(data_in_shellby *shellby_data_store);

/* environment1.c */
char *_getenv(const char *known_name, char **_environment);
int _environment(data_in_shellby *shellby_data_store);

/* environment2.c */
char *copy_info(char *known_name, char *value);
void set_environment(char *known_name, char *value, data_in_shellby *shellby_data_store);
int _setenvironment(data_in_shellby *shellby_data_store);
int _unsetenvironment(data_in_shellby *shellby_data_store);

/* change_dir.c */
void change_dir_dot(data_in_shellby *shellby_data_store);
void change_dir_to(data_in_shellby *shellby_data_store);
void change_dir_previous(data_in_shellby *shellby_data_store);
void change_dir_to_home(data_in_shellby *shellby_data_store);

/* change_dir_shell.c */
int change_dir_shell(data_in_shellby *shellby_data_store);

/* get_builtin */
int (*get_builtin(char *command))(data_in_shellby *shellby_data_store);

/* exit_shellby.c */
int exit_shellby(data_in_shellby *shellby_data_store);

/* auxillary_stdlib.c */
int get_length(int n);
char *auxillary_itoa(int n);
int _atoi(char *shellby_string);

/* auxillary_error1.c */
char *strcat_change_dir(data_in_shellby *, char *, char *, char *);
char *error_get_change_dir(data_in_shellby *shellby_data_store);
char *error_not_found(data_in_shellby *shellby_data_store);
char *error_exit_shellby(data_in_shellby *shellby_data_store);

/* auxillary_error2.c */
char *error_get_alias(char **arguments);
char *error_environment(data_in_shellby *shellby_data_store);
char *error_syntax(char **arguments);
char *error_permission(char **arguments);
char *error_path_126(data_in_shellby *shellby_data_store);

/* get_error.c */
int get_error(data_in_shellby *shellby_data_store, int error_value);

/* get_signed_int.c */
void get_signed_int(int signed_i);

/* auxillary_help.c */
void auxillary_help_environment(void);
void auxillary_help_setenv(void);
void auxillary_help_unsetenv(void);
void auxillary_help_general(void);
void auxillary_help_exit(void);

/* auxillary_help2.c */
void auxillary_help(void);
void auxillary_help_alias(void);
void auxillary_help_change_dir(void);

/* get_help.c */
int get_help(data_in_shellby *shellby_data_store);

#endif
