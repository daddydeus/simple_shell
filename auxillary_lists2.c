#include "thomas_shellby.h"

/**
 * add_rvariable_node – This function is one that adds a variable at the end
 * of a r_variable list.
 * @header: This is the header of the linked list.
 * @length_of_var: This specifies the length of the variable.
 * @variable_value: This specifies the value of the variable.
 * @length_of_val: This specifies the length of the value.
 * Return: address of the header.
 */
r_variable *add_rvariable_node(r_variable **header, int length_of_var, char *variable_value, int length_of_val)
{
	r_variable *current, *temporary;

	current = malloc(sizeof(r_variable));
	if (current == NULL)
		return (NULL);

	current->len_variable = length_of_var;
	current->variable_value = variable_value;
	current->length_of_variable_value = length_of_val;

	current->next = NULL;
	temporary = *header;

	if (temporary == NULL)
	{
		*header = current;
	}
	else
	{
		while (temporary->next != NULL)
			temporary = temporary->next;
		temporary->next = current;
	}

	return (*header);
}

/**
 * free_rvariable_list – This is a function that frees a r_variable list
 * @header: This is the header of the linked list.
 * Return: no return.
 */
void free_rvariable_list(r_variable **header)
{
	r_variable *temporary;
	r_variable *curr_ent;

	if (header != NULL)
	{
		curr_ent = *header;
		while ((temporary = curr_ent) != NULL)
		{
			curr_ent = curr_ent->next;
			free(temporary);
		}
		*header = NULL;
	}
}
