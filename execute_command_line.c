#include "thomas_shellby.h"

/**
 * execute_command_line – This is a function that finds builtins and commands to execute
 * @shellby_data_store: This is the data on the relevant arguments
 * Return: 1 on success.
 */
int execute_command_line(data_in_shellby *shellby_data_store)
{
	int (*builtin)(data_in_shellby *shellby_data_store);

	if (shellby_data_store->arguments[0] == NULL)
		return (1);

	builtin = get_builtin(shellby_data_store->arguments[0]);

	if (builtin != NULL)
		return (builtin(shellby_data_store));

	return (command_execute(shellby_data_store));
}
