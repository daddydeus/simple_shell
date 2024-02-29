#include "thomas_shellby.h"

/**
 * change_dir_shell – This is a command that changes the current directory to an input specified directory
 * @shellby_data_store: This is the container with the relevant data
 * Return: 1 on success
 */
int change_dir_shell(data_in_shellby *shellby_data_store)
{
	char *dir;
	int to_home, to_home2, to_double_dash;

	dir = shellby_data_store->arguments[1];

	if (dir != NULL)
	{
		to_home = _strcmp("$HOME", dir);
		to_home2 = _strcmp("~", dir);
		to_double_dash = _strcmp("--", dir);
	}

	if (dir == NULL || !to_home || !to_home2 || !to_double_dash)
	{
		change_dir_to_home(shellby_data_store);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		change_dir_previous(shellby_data_store);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		change_dir_dot(shellby_data_store);
		return (1);
	}

	change_dir_to(shellby_data_store);

	return (1);
}
