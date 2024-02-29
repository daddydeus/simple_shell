#include "thomas_shellby.h"

/**
 * cmp_environment_known_name – This is a function that compares environment variables names with the known_name passed.
 * @nenvironment: This is the known_name of the environment variable
 * @known_name: This is the known_name that is passed
 * Return: 0 if are not equal. Another value if they are.
 */
int cmp_environment_known_name(const char *nenvironment, const char *known_name)
{
	int i;

	for (i = 0; nenvironment[i] != '='; i++)
	{
		if (nenvironment[i] != known_name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * _getenvironment – This is our previously defined function that gets an environment variable
 * @known_name: This is the already specified known_name of our chosen environment variable
 * @_environment: This is the chosen environment variable
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *_getenvironment(const char *known_name, char **_environment)
{
	char *shellby_tr_environment;
	int i, movies;

	/* Now we initialize the shellby_tr_environment value */
	shellby_tr_environment = NULL;
	movies = 0;
	/* Lets begin by comparing all environment variables */
	/* The variable environment was declared in the Thomas Shellby header file */
	for (i = 0; _environment[i]; i++)
	{
		/* Here if the known_name and environment are equal */
		movies = cmp_environment_known_name(_environment[i], known_name);
		if (movies)
		{
			shellby_tr_environment = _environment[i];
			break;
		}
	}

	return (shellby_tr_environment + movies);
}

/**
 * _environment – This is a function that prints the evironment variables from our session
 * @shellby_data_store: This is the data relevant store.
 * Return: 1 on success.
 */
int _environment(data_in_shellby *shellby_data_store)
{
	int i, j_shellby;

	for (i = 0; shellby_data_store->_environment[i]; i++)
	{

		for (j_shellby = 0; shellby_data_store->_environment[i][j_shellby]; j_shellby++)
			;

		write(STDOUT_FILENO, shellby_data_store->_environment[i], j_shellby);
		write(STDOUT_FILENO, "\n", 1);
	}
	shellby_data_store->last.status = 0;

	return (1);
}
