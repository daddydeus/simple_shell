#include "thomas_shellby.h"

/**
 * get_builtin – This is the function that calls all builtin commands in the argument
 * @command: This is the built in command specified
 * Return: function pointer of the builtin command
 */
int (*get_builtin(char *command))(data_in_shellby *)
{
	builtin_t builtin[] = {
		{ "environment", _environment },
		{ "exit", exit_shellby },
		{ "setenvironment", _setenvironment },
		{ "unsetenvironment", _unsetenvironment },
		{ "change_dir", change_dir_shell },
		{ "help", get_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].known_name; i++)
	{
		if (_strcmp(builtin[i].known_name, command) == 0)
			break;
	}

	return (builtin[i].dtp_function);
}
