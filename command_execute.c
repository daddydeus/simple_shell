#include "thomas_shellby.h"

/**
 * is_cdir – This is a function that checks for ":" to see if it is in the current directory.
 * @path: This is a char data type pointer variable.
 * @i: This is an  int data type pointer of index.
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int is_cdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * _which – This is a function that locates a command
 * @command: This is the particular command name
 * @_environment: This is our environment variable
 * Return: location of the command.
 */
char *_which(char *command, char **_environment)
{
	char *path, *shellby_tr_path, *token_path, *dir;
	int length_dir, length_command, i;
	struct stat st;

	path = _setenvironment("path", _environment);
	if (path)
	{
		shellby_tr_path = _strdup(path);
		length_command = _strlen(command);
		token_path = _strtok(shellby_tr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_cdir(path, &i))
				if (stat(command, &st) == 0)
					return (command);
			length_dir = _strlen(token_path);
			dir = malloc(length_dir + length_command + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, command);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(shellby_tr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(shellby_tr_path);
		if (stat(command, &st) == 0)
			return (command);
		return (NULL);
	}
	if (command[0] == '/')
		if (stat(command, &st) == 0)
			return (command);
	return (NULL);
}

/**
 * is_executable – This is a function that determines if the command is an executable file
 * @shellby_data_store: This is our data structure store
 * Return: 0 if is not an executable, other number if it does
 */
int is_executable(data_in_shellby *shellby_data_store)
{
	struct stat st;
	int i;
	char *user_input;

	user_input = shellby_data_store->arguments[0];
	for (i = 0; user_input[i]; i++)
	{
		if (user_input[i] == '.')
		{
			if (user_input[i + 1] == '.')
				return (0);
			if (user_input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (user_input[i] == '/' && i != 0)
		{
			if (user_input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(user_input + i, &st) == 0)
	{
		return (i);
	}
	get_error(shellby_data_store, 127);
	return (-1);
}

/**
 * check_error_command – This is a function that verifies if user has permissions to access a certain file or directory
 * @dir: This is the variable for our destination directory
 * @shellby_data_store: This is our data structure store
 * Return: 1 if there is an error, 0 if not
 */
int check_error_command(char *dir, data_in_shellby *shellby_data_store)
{
	if (dir == NULL)
	{
		get_error(shellby_data_store, 127);
		return (1);
	}

	if (_strcmp(shellby_data_store->arguments[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error(shellby_data_store, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(shellby_data_store->arguments[0], X_OK) == -1)
		{
			get_error(shellby_data_store, 126);
			return (1);
		}
	}

	return (0);
}

/**
* command_exec – This is a function that executes various lines of commands
 * @shellby_data_store: This is the relevant arguments and user_input
 * Return: 1 on success.
 */
int command_execute(data_in_shellby *shellby_data_store)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = is_executable(shellby_data_store);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _which(shellby_data_store->arguments[0], shellby_data_store->_environment);
		if (check_error_command(dir, shellby_data_store) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _which(shellby_data_store->arguments[0], shellby_data_store->_environment);
		else
			dir = shellby_data_store->arguments[0];
		execve(dir + exec, shellby_data_store->arguments, shellby_data_store->_environment);
	}
	else if (pd < 0)
	{
		perror(shellby_data_store->argument_vect[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	shellby_data_store->last.status = state / 256;
	return (1);
}
