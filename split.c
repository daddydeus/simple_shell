#include "thomas_shellby.h"

/**
 * swap_char – This is the function that swaps | and & for non-printed characters
 * @user_input: This is our user_input string
 * @bool: This is simply a type of swap
 * Return: swapped string
 */
char *swap_char(char *user_input, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; user_input[i]; i++)
		{
			if (user_input[i] == '|')
			{
				if (user_input[i + 1] != '|')
					user_input[i] = 16;
				else
					i++;
			}

			if (user_input[i] == '&')
			{
				if (user_input[i + 1] != '&')
					user_input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; user_input[i]; i++)
		{
			user_input[i] = (user_input[i] == 16 ? '|' : user_input[i]);
			user_input[i] = (user_input[i] == 12 ? '&' : user_input[i]);
		}
	}
	return (user_input);
}

/**
 * add_nodes – This function add separators and lines of commands into any available lists
 * @header_separators: This is the head of the separator list
 * @header_length: This is the head of lines of commands list
 * @user_input: This is our user_input string
 * Return: no return
 */
void add_nodes(separators_list **header_separators, command_line_list **header_length, char *user_input)
{
	int i;
	char *command_line;

	user_input = swap_char(user_input, 0);

	for (i = 0; user_input[i]; i++)
	{
		if (user_input[i] == ';')
			add_separators_node_end(header_separators, user_input[i]);

		if (user_input[i] == '|' || user_input[i] == '&')
		{
			add_separators_node_end(header_separators, user_input[i]);
			i++;
		}
	}

	command_line = _strtok(user_input, ";|&");
	do {
		command_line = swap_char(command_line, 1);
		add_command_line_node_end(header_length, command_line);
		command_line = _strtok(NULL, ";|&");
	} while (command_line != NULL);

}

/**
 * go_nextn – This is the function that causes the program go to the next command line stored
 * @list_separators: separator list
 * @list_length: command line list
 * @shellby_data_store: data structure
 * Return: no return
 */
void go_nextn(separators_list **list_separators, command_line_list **list_length, data_in_shellby *shellby_data_store)
{
	int loop_separators;
	separators_list *ls_s;
	command_line_list *ls_l;

	loop_separators = 1;
	ls_s = *list_separators;
	ls_l = *list_length;

	while (ls_s != NULL && loop_separators)
	{
		if (shellby_data_store->last_status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_separators = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->nextn, ls_s = ls_s->nextn;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_separators = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->nextn, ls_s = ls_s->nextn;
		}
		if (ls_s != NULL && !loop_separators)
			ls_s = ls_s->nextn;
	}

	*list_separators = ls_s;
	*list_length = ls_l;
}

/**
 * split_commands – This function splits lines of commands according to the separators ;, | and &, and executes them
 * @shellby_data_store: This is our data structure
 * @user_input: This is our user generated user_input string
 * Return: 0 to exit, 1 to continue
 */
int split_commands(data_in_shellby *shellby_data_store, char *user_input)
{

	separators_list *header_separators, *list_separators;
	command_line_list *header_length, *list_length;
	int loop;

	header_separators = NULL;
	header_length = NULL;

	add_nodes(&header_separators, &header_length, user_input);

	list_separators = header_separators;
	list_length = header_length;

	while (list_length != NULL)
	{
		shellby_data_store->user_input = list_length->command_line;
		shellby_data_store->arguments = split_command_line(shellby_data_store->user_input);
		loop = execute_command_line(shellby_data_store);
		free(shellby_data_store->arguments);

		if (loop == 0)
			break;

		go_nextn(&list_separators, &list_length, shellby_data_store);

		if (list_length != NULL)
			list_length = list_length->nextn;
	}

	free_separators_list(&header_separators);
	free_command_line_list(&header_length);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * split_command_line – This si the function that tokenizes the generated user_input string
 * @user_input: This is our generated user_input string.
 * Return: string splitted.
 */
char **split_command_line(char *user_input)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOKEN_BUFFER_SIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(user_input, DELIMITER);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOKEN_BUFFER_SIZE;
			tokens = _reallocdp(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, DELIMITER);
		tokens[i] = token;
	}

	return (tokens);
}
