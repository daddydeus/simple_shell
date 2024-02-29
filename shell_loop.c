#include "thomas_shellby.h"

/**
 * without_user_input – This is a function that deletes comments from within the user input
 * @user_in: This is another variable for our input string
 * Return: input without comments
 */
char *without_user_input(char *user_in)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; user_in[i]; i++)
	{
		if (user_in[i] == '#')
		{
			if (i == 0)
			{
				free(user_in);
				return (NULL);
			}

			if (user_in[i - 1] == ' ' || user_in[i - 1] == '\t' || user_in[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		user_in = _realloc(user_in, i, up_to + 1);
		user_in[up_to] = '\0';
	}

	return (user_in);
}

/**
 * shell_loop – This is the function that causes the everlasting loop of the shell prompt
 * @shellby_data_store: This is our data store filled with argument_vect, user_input, arguments
 * Return: no return.
 */
void shell_loop(data_in_shellby *shellby_data_store)
{
	int loop, i_eof;
	char *user_input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		user_input = read_command_line(&i_eof);
		if (i_eof != -1)
		{
			user_input = without_user_input(user_input);
			if (user_input == NULL)
				continue;

			if (check_syntax_error(shellby_data_store, user_input) == 1)
			{
				shellby_data_store->last_status = 2;
				free(user_input);
				continue;
			}
			user_input = rep_variable(user_input, shellby_data_store);
			loop = split_commands(shellby_data_store, user_input);
			shellby_data_store->count += 1;
			free(user_input);
		}
		else
		{
			loop = 0;
			free(user_input);
		}
	}
}
