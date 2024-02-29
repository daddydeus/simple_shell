#include "thomas_shellby.h"

/**
 * copy_info – This is a function that copies info to create a new environment or alias
 * @known_name: This is the known_name of the environment or its alias
 * @value: This is the value of the environment or its alias
 * Return: current environment or alias.
 */
char *copy_info(char *known_name, char *value)
{
	char *current;
	int length_known_name, length_value, length;

	length_known_name = _strlen(known_name);
	length_value = _strlen(value);
	length = length_known_name + length_value + 2;
	current = malloc(sizeof(char) * (length));
	_strcpy(current, known_name);
	_strcat(current, "=");
	_strcat(current, value);
	_strcat(current, "\0");

	return (current);
}

/**
 * set_environment – This is a function that sets an environment variable from a desired input 
 * @known_name: This is the known_name of the chosen environment variable
 * @value: This is the value of the chosen environment variable
 * @shellby_data_store: This is the data structure environment value
 * Return: no return
 */
void set_environment(char *known_name, char *value, data_in_shellby *shellby_data_store)
{
	int i;
	char *variable_environment, *known_name_environment;

	for (i = 0; shellby_data_store->_environment[i]; i++)
	{
		variable_environment = _strdup(shellby_data_store->_environment[i]);
		known_name_environment = _strtok(variable_environment, "=");
		if (_strcmp(known_name_environment, known_name) == 0)
		{
			free(shellby_data_store->_environment[i]);
			shellby_data_store->_environment[i] = copy_info(known_name_environment, value);
			free(variable_environment);
			return;
		}
		free(variable_environment);
	}

	shellby_data_store->_environment = _reallocdp(shellby_data_store->_environment, i, sizeof(char *) * (i + 2));
	shellby_data_store->_environment[i] = copy_info(known_name, value);
	shellby_data_store->_environment[i + 1] = NULL;
}

/**
 * _setenvironment – This is a function that compares different environment variables names with the known_name passed.
 * @shellby_data_store: This is the data on environment known_name and environment value
 * Return: 1 on success.
 */
int _setenvironment(data_in_shellby *shellby_data_store)
{

	if (shellby_data_store->arguments[1] == NULL || shellby_data_store->arguments[2] == NULL)
	{
		get_error(shellby_data_store, -1);
		return (1);
	}

	set_environment(shellby_data_store->arguments[1], shellby_data_store->arguments[2], shellby_data_store);

	return (1);
}

/**
 * _unsetenvironment – This is a function that deletes an environment variable
 * @shellby_data_store: This is the data from environment known_name
 * Return: 1 on success.
 */
int _unsetenvironment(data_in_shellby *shellby_data_store)
{
	char **realloc_environment;
	char *variable_environment, *known_name_environment;
	int i, j_shellby, k_shellby;

	if (shellby_data_store->arguments[1] == NULL)
	{
		get_error(shellby_data_store, -1);
		return (1);
	}
	k_shellby = -1;
	for (i = 0; shellby_data_store->_environment[i]; i++)
	{
		variable_environment = _strdup(shellby_data_store->_environment[i]);
		known_name_environment = _strtok(variable_environment, "=");
		if (_strcmp(known_name_environment, shellby_data_store->arguments[1]) == 0)
		{
			k_shellby = i;
		}
		free(variable_environment);
	}
	if (k_shellby == -1)
	{
		get_error(shellby_data_store, -1);
		return (1);
	}
	realloc_environment = malloc(sizeof(char *) * (i));
	for (i = j_shellby = 0; shellby_data_store->_environment[i]; i++)
	{
		if (i != k_shellby)
		{
			realloc_environment[j_shellby] = shellby_data_store->_environment[i];
			j_shellby++;
		}
	}
	realloc_environment[j_shellby] = NULL;
	free(shellby_data_store->_environment[k_shellby]);
	free(shellby_data_store->_environment);
	shellby_data_store->_environment = realloc_environment;
	return (1);
}
