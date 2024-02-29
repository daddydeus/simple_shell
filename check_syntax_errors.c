#include "thomas_shellby.h"

/**
 * repeated_char – This is a function that counts the repetitions of any given character
 * @user_input: This is the user inputted string
 * @i: This is the variable for index
 * Return: repetitions
 */
int repeated_char(char *user_input, int i)
{
	if (*(user_input - 1) == *user_input)
		return (repeated_char(user_input - 1, i + 1));

	return (i);
}

/**
 * error_separators_op – This is the function that finds syntax errors in the user input
 * @user_input: This is the user inputted string
 * @i: This is the variable for index
 * @last: This is the identifier for the last character that was read
 * Return: index of error. 0 when there are no errors
 */
int error_separators_op(char *user_input, int i, char last)
{
	int cou_nter;

	cou_nter = 0;
	if (*user_input == '\0')
		return (0);

	if (*user_input == ' ' || *user_input == '\t')
		return (error_separators_op(user_input + 1, i + 1, last));

	if (*user_input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*user_input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			cou_nter = repeated_char(user_input, 0);
			if (cou_nter == 0 || cou_nter > 1)
				return (i);
		}
	}

	if (*user_input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			cou_nter = repeated_char(user_input, 0);
			if (cou_nter == 0 || cou_nter > 1)
				return (i);
		}
	}

	return (error_separators_op(user_input + 1, i + 1, *user_input));
}

/**
 * first_char – This is a function that finds the index of the first character
 * @user_input: This is the user inputted string
 * @i: This is the variable that defines our index
 * Return: 1 if there is an error. 0 in other case.
 */
int first_char(char *user_input, int *i)
{

	for (*i = 0; user_input[*i]; *i += 1)
	{
		if (user_input[*i] == ' ' || user_input[*i] == '\t')
			continue;

		if (user_input[*i] == ';' || user_input[*i] == '|' || user_input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_syntax_error – This is the function that prints when a syntax error is found
 * @shellby_data_store: This is the data structure store
 * @user_input: This is the user inputted string
 * @i: This variable now represents the index of the error
 * @bool: This is a variable that will be used to control on_screen error
 * Return: no return
 */
void print_syntax_error(data_in_shellby *shellby_data_store, char *user_input, int i, int bool)
{
	char *on_screen, *on_screen2, *on_screen3, *error, *count;
	int leng_th;

	if (user_input[i] == ';')
	{
		if (bool == 0)
			on_screen = (user_input[i + 1] == ';' ? ";;" : ";");
		else
			on_screen = (user_input[i - 1] == ';' ? ";;" : ";");
	}

	if (user_input[i] == '|')
		on_screen = (user_input[i + 1] == '|' ? "||" : "|");

	if (user_input[i] == '&')
		on_screen = (user_input[i + 1] == '&' ? "&&" : "&");

	on_screen2 = ": Syntax error: \"";
	on_screen3 = "\" unexpected\n";
	count = auxillary_itoa(shellby_data_store->count);
	leng_th = _strlen(shellby_data_store->argument_vect[0]) + _strlen(count);
	leng_th += _strlen(on_screen) + _strlen(on_screen2) + _strlen(on_screen3) + 2;

	error = malloc(sizeof(char) * (leng_th + 1));
	if (error == 0)
	{
		free(count);
		return;
	}
	_strcpy(error, shellby_data_store->argument_vect[0]);
	_strcat(error, ": ");
	_strcat(error, count);
	_strcat(error, on_screen2);
	_strcat(error, on_screen);
	_strcat(error, on_screen3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, leng_th);
	free(error);
	free(count);
}

/**
 * check_syntax_error – This is a mid level function that is designed to find and print a syntax error
 * @shellby_data_store: This is our data structure store
 * @user_input: This is the user inputted string
 * Return: 1 if there is an error. 0 in other case
 */
int check_syntax_error(data_in_shellby *shellby_data_store, char *user_input)
{
	int start_point = 0;
	int f_char = 0;
	int i = 0;

	f_char = first_char(user_input, &start_point);
	if (f_char == -1)
	{
		print_syntax_error(shellby_data_store, user_input, start_point, 0);
		return (1);
	}

	i = error_separators_op(user_input + start_point, 0, *(user_input + start_point));
	if (i != 0)
	{
		print_syntax_error(shellby_data_store, user_input, start_point + i, 1);
		return (1);
	}

	return (0);
}
