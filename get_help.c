#include "thomas_shellby.h"

/**
 * get_help – This is the function that retrieves help messages and manuals according to the builtin commands
 * @shellby_data_store: This is the data structure store file containing arguments and input
 * Return: Return 0
*/
int get_help(data_in_shellby *shellby_data_store)
{

	if (shellby_data_store->arguments[1] == 0)
		auxillary_help_general();
	else if (_strcmp(shellby_data_store->arguments[1], "setenvironment") == 0)
		auxillary_help_setenvironment();
	else if (_strcmp(shellby_data_store->arguments[1], "environment") == 0)
		auxillary_help_environment();
	else if (_strcmp(shellby_data_store->arguments[1], "unsetenvironment") == 0)
		auxillary_help_unsetenvironment();
	else if (_strcmp(shellby_data_store->arguments[1], "help") == 0)
		auxillary_help();
	else if (_strcmp(shellby_data_store->arguments[1], "exit") == 0)
		auxillary_help_exit();
	else if (_strcmp(shellby_data_store->arguments[1], "change_dir") == 0)
		auxillary_help_change_dir();
	else if (_strcmp(shellby_data_store->arguments[1], "alias") == 0)
		auxillary_help_alias();
	else
		write(STDERR_FILENO, shellby_data_store->arguments[0],
		      _strlen(shellby_data_store->arguments[0]));

	shellby_data_store->last_status = 0;
	return (1);
}
