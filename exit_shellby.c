#include "thomas_shellby.h"

/**
 * exit_shellby – This is the command that exits the Thomas Shellby script
 * @shellby_data_store: This is the data on last_status and arguments
 * Return: 0 on success.
 */
int exit_shell(data_in_shellby *shellby_data_store)
{
	unsigned int stat_us;
	int is_digit;
	int stringy_length;
	int wotowoto_number;

	if (shellby_data_store->arguments[1] != NULL)
	{
		stat_us = _atoi(shellby_data_store->arguments[1]);
		is_digit = _isdigit(shellby_data_store->arguments[1]);
		stringy_length = _strlen(shellby_data_store->arguments[1]);
		wotowoto_number = stat_us > (unsigned int)INT_MAX;
		if (!is_digit || stringy_length > 10 || wotowoto_number)
		{
			get_error(shellby_data_store, 2);
			shellby_data_store->last_status = 2;
			return (1);
		}
		shellby_data_store->last_status = (stat_us % 256);
	}
	return (0);
}
