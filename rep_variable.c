#include "thomas_shellby.h"

/**
 * check_environment – This is the function that checks if the user inputted variable is an environment variable or not
 * @head: This is the head of the linked list
 * @user_in: This is our user generated input string
 * @shellby_data: This is our shellby_data structure
 * Return: no return
 */
void check_environment(r_variable **head, char *user_in, data_in_shellby *data)
{
	int row, chr, j_shellby, length_of_val;
	char **_envr;

	_envr = data->_environment;
	for (row = 0; _envr[row]; row++)
	{
		for (j_shellby = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				length_of_val = _strlen(_envr[row] + chr + 1);
				add_rvariable_node(head, j_shellby, _envr[row] + chr + 1, length_of_val);
				return;
			}

			if (user_in[j_shellby] == _envr[row][chr])
				j_shellby++;
			else
				break;
		}
	}

	for (j_shellby = 0; user_in[j_shellby]; j_shellby++)
	{
		if (user_in[j_shellby] == ' ' || user_in[j_shellby] == '\t' || user_in[j_shellby] == ';' || user_in[j_shellby] == '\n')
			break;
	}

	add_rvariable_node(head, j_shellby, NULL, 0);
}

/**
 * check_vars – This is the function that is used to check if the typed variable is $$ or $?
 * @head: This is the header of the linked list
 * @user_in: This is our user inputted string
 * @st: This int defines the last status of the Shell
 * @shellby_data: This is the store for our shellby_data structure
 * Return: no return
 */
int check_vars(r_variable **head, char *user_in, char *st, data_in_shellby *shellby_data)
{
	int i, last_st, last_pd;

	last_st = _strlen(st);
	last_pd = _strlen(shellby_data->shellby_pid);

	for (i = 0; user_in[i]; i++)
	{
		if (user_in[i] == '$')
		{
			if (user_in[i + 1] == '?')
				add_rvariable_node(head, 2, st, last_st), i++;
			else if (user_in[i + 1] == '$')
				add_rvariable_node(head, 2, shellby_data->shellby_pid, last_pd), i++;
			else if (user_in[i + 1] == '\n')
				add_rvariable_node(head, 0, NULL, 0);
			else if (user_in[i + 1] == '\0')
				add_rvariable_node(head, 0, NULL, 0);
			else if (user_in[i + 1] == ' ')
				add_rvariable_node(head, 0, NULL, 0);
			else if (user_in[i + 1] == '\t')
				add_rvariable_node(head, 0, NULL, 0);
			else if (user_in[i + 1] == ';')
				add_rvariable_node(head, 0, NULL, 0);
			else
				check_environment(head, user_in + i, shellby_data);
		}
	}

	return (i);
}

/**
 * replaced_user_input – This is the function that replaces string with variables
 * @header: This is the header of our linked list
 * @user_input: This variable declares our user_input string
 * @current_user_input: This declares the latest inputted current user_input string (replaced)
 * @nlength: This represents the current length of the string 
 * Return: replaced string
 */
char *replaced_user_input(r_variable **header, char *user_input, char *current_user_input, int nlength)
{
	r_variable *indx;
	int i, j_shellby, k_shellby;

	indx = *header;
	for (j_shellby = i = 0; i < nlength; i++)
	{
		if (user_input[j_shellby] == '$')
		{
			if (!(indx->length_of_variable) && !(indx->length_of_variable_value))
			{
				current_user_input[i] = user_input[j_shellby];
				j_shellby++;
			}
			else if (indx->length_of_variable && !(indx->length_of_variable_value))
			{
				for (k_shellby = 0; k_shellby < indx->length_of_variable; k_shellby++)
					j_shellby++;
				i--;
			}
			else
			{
				for (k_shellby = 0; k_shellby < indx->length_of_variable_value; k_shellby++)
				{
					current_user_input[i] = indx->val[k_shellby];
					i++;
				}
				j_shellby += (indx->length_of_variable);
				i--;
			}
			indx = indx->nextn;
		}
		else
		{
			current_user_input[i] = user_input[j_shellby];
			j_shellby++;
		}
	}

	return (current_user_input);
}

/**
 * rep_variable – This command calls a function to convert strings into variabless
 * @user_input: This is our user_input string
 * @shellby_data_store: This is the store for all our shellby_data structure
 * Return: replaced string
 */
char *rep_variable(char *user_input, data_in_shellby *shellby_data_store)
{
	r_variable *header, *indx;
	char *last_status, *current_user_input;
	int olength, nlength;

	last_status = auxillary_itoa(shellby_data_store->last_status);
	header = NULL;

	olength = check_vars(&header, user_input, last_status, shellby_data_store);

	if (header == NULL)
	{
		free(last_status);
		return (user_input);
	}

	indx = header;
	nlength = 0;

	while (indx != NULL)
	{
		nlength += (indx->length_of_variable_value - indx->length_of_variable);
		indx = indx->nextn;
	}

	nlength += olength;

	current_user_input = malloc(sizeof(char) * (nlength + 1));
	current_user_input[nlength] = '\0';

	current_user_input = replaced_user_input(&header, user_input, current_user_input, nlength);

	free(user_input);
	free(last_status);
	free_rvariable_list(&header);

	return (current_user_input);
}
