#include "thomas_shellby.h"

/**
 * get_error – This is the function that calls the error according the builtin command, syntax or permission
 * @shellby_data_store: This is the data structure that contains all known arguments
 * @error_value: This is quite simply the error value
 * Return: error
 */
int get_error(data_in_shellby *shellby_data_store, int error_value)
{
	char *error;

	switch (error_value)
	{
	case -1:
		error = error_environment(shellby_data_store);
		break;
	case 126:
		error = error_path_126(shellby_data_store);
		break;
	case 127:
		error = error_not_found(shellby_data_store);
		break;
	case 2:
		if (_strcmp("exit", shellby_data_store->arguments[0]) == 0)
			error = error_exit_shellby(shellby_data_store);
		else if (_strcmp("change_dir", shellby_data_store->arguments[0]) == 0)
			error = error_get_change_dir(shellby_data_store);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	shellby_data_store->last_status = error_value;
	return (error_value);
}
