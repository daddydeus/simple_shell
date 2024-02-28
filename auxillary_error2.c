#include "thomas_shellby.h"

/**
 * error_environment – This is the error message for environment in get_environment.
 * @shellby_data_store: This is the relevant counter and arguments
 * Return: error message.
 */
char *error_environment(data_in_shellby *shellby_data_store)
{
	int length;
	char *error;
	char *version_string;
	char *on_screen;

	version_string = auxillary_itoa(shellby_data_store->counter);
	on_screen = ": Unable to add/remove from environment\n";
	length = _strlen(shellby_data_store->argument_vect[0]) + _strlen(version_string);
	length += _strlen(shellby_data_store->arguments[0]) + _strlen(on_screen) + 4;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(version_string);
		return (NULL);
	}

	_strcpy(error, shellby_data_store->argument_vect[0]);
	_strcat(error, ": ");
	_strcat(error, version_string);
	_strcat(error, ": ");
	_strcat(error, shellby_data_store->arguments[0]);
	_strcat(error, on_screen);
	_strcat(error, "\0");
	free(version_string);

	return (error);
}
/**
 * error_path_126 – This is the error message for wrong path and access denied.
 * @shellby_data_store: This is the relevant counter and arguments.
 *
 * Return: The error string.
 */
char *error_path_126(data_in_shellby *shellby_data_store)
{
	int length;
	char *version_string;
	char *error;

	version_string = auxillary_itoa(shellby_data_store->counter);
	length = _strlen(shellby_data_store->argument_vect[0]) + _strlen(version_string);
	length += _strlen(shellby_data_store->arguments[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(version_string);
		return (NULL);
	}
	_strcpy(error, shellby_data_store->argument_vect[0]);
	_strcat(error, ": ");
	_strcat(error, version_string);
	_strcat(error, ": ");
	_strcat(error, shellby_data_store->arguments[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(version_string);
	return (error);
}
