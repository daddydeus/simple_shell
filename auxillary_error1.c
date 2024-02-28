#include "thomas_shellby.h"

/**
 * strcat_change_dir – This is a function that integrates the message for change directory error
 *
 * @shellby_data_store: This is the data relevant directory to be used
 * @on_screen: This is the output message we need to print
 * @error: This is the error output message
 * @version_string: This is simply a string data type that holds counter lines
 * Return: error message
 */
char *strcat_change_dir(data_in_shellby *shellby_data_store, char *on_screen, char *error, char *version_string)
{
	char *wrong_entry;

	_strcpy(error, shellby_data_store->argument_vect[0]);
	_strcat(error, ": ");
	_strcat(error, version_string);
	_strcat(error, ": ");
	_strcat(error, shellby_data_store->arguments[0]);
	_strcat(error, on_screen);
	if (shellby_data_store->arguments[1][0] == '-')
	{
		wrong_entry = malloc(3);
		wrong_entry[0] = '-';
		wrong_entry[1] = shellby_data_store->arguments[1][1];
		wrong_entry[2] = '\0';
		_strcat(error, wrong_entry);
		free(wrong_entry);
	}
	else
	{
		_strcat(error, shellby_data_store->arguments[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * error_get_change_dir – This is an error message for the change directory command in get_change_dir
 * @shellby_data_store: This is the relevant directory
 * Return: Error message
 */
char *error_get_change_dir(data_in_shellby *shellby_data_store)
{
	int length, length_id;
	char *error, *version_string, *on_screen;

	version_string = auxillary_itoa(shellby_data_store->counter);
	if (shellby_data_store->arguments[1][0] == '-')
	{
		on_screen = ": Unacceptable entry ";
		length_id = 2;
	}
	else
	{
		on_screen = ": Sorry I cannot change directory to ";
		length_id = _strlen(shellby_data_store->arguments[1]);
	}

	length = _strlen(shellby_data_store->argument_vect[0]) + _strlen(shellby_data_store->arguments[0]);
	length += _strlen(version_string) + _strlen(on_screen) + length_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(version_string);
		return (NULL);
	}

	error = strcat_change_dir(shellby_data_store, on_screen, error, version_string);

	free(version_string);

	return (error);
}

/**
 * error_not_found – This is a generic error message that will be outputted when the command is not found
 * @shellby_data_store: This is the relevant counter and arguments
 * Return: Error message
 */
char *error_not_found(data_in_shellby *shellby_data_store)
{
	int length;
	char *error;
	char *version_string;

	version_string = auxillary_itoa(shellby_data_store->counter);
	length = _strlen(shellby_data_store->argument_vect[0]) + _strlen(version_string);
	length += _strlen(shellby_data_store->arguments[0]) + 16;
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
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(version_string);
	return (error);
}

/**
 * error_exit_shellby – This is simply a generic error message for the exit command in get_exit
 * @shellby_data_store: data relevant (counter, arguments)
 *
 * Return: Error message
 */
char *error_exit_shellby(data_in_shellby *shellby_data_store)
{
	int length;
	char *error;
	char *version_string;

	version_string = auxillary_itoa(shellby_data_store->counter);
	length = _strlen(shellby_data_store->argument_vect[0]) + _strlen(version_string);
	length += _strlen(shellby_data_store->arguments[0]) + _strlen(shellby_data_store->arguments[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(version_string);
		return (NULL);
	}
	_strcpy(error, shellby_data_store->argument_vect[0]);
	_strcat(error, ": ");
	_strcat(error, version_string);
	_strcat(error, ": ");
	_strcat(error, shellby_data_store->arguments[0]);
	_strcat(error, ": Unacceptable entry: ");
	_strcat(error, shellby_data_store->arguments[1]);
	_strcat(error, "\n\0");
	free(version_string);

	return (error);
}
