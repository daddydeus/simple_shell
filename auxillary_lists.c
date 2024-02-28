#include "thomas_shellby.h"

/**
 * add_separators_node_end – This function adds a separator found at the end
 * of a separators_list.
 * @header: header of the linked list.
 * @separators: separator found (; | &).
 * Return: address of the header.
 */
separators_list *add_separators_node_end(separators_list **header, char separators)
{
	separators_list *current, *temporary;

	current = malloc(sizeof(separators_list));
	if (current == NULL)
		return (NULL);

	current->separator = separators;
	current->nextn = NULL;
	temporary = *header;

	if (temporary == NULL)
	{
		*header = current;
	}
	else
	{
		while (temporary->nextn != NULL)
			temporary = temporary->nextn;
		temporary->nextn = current;
	}

	return (*header);
}

/**
 * free_separators_list – This function frees a separators_list
 * @header: header of the linked list.
 * Return: no return.
 */
void free_separators_list(separators_list **header)
{
	separators_list *temporary;
	separators_list *curr_ent;

	if (header != NULL)
	{
		curr_ent = *header;
		while ((temporary = curr_ent) != NULL)
		{
			curr_ent = curr_ent->nextn;
			free(temporary);
		}
		*header = NULL;
	}
}

/**
 * add_command_line_node_end – This function adds a line of commands at the end
 * of a command_line_list.
 * @header: header of the linked list.
 * @command_line: line of commands.
 * Return: address of the header.
 */
command_line_list *add_command_line_node_end(command_line_list **header, char *command_line)
{
	command_line_list *current, *temporary;

	current = malloc(sizeof(command_line_list));
	if (current == NULL)
		return (NULL);

	current->command_line = command_line;
	current->nextn = NULL;
	temporary = *header;

	if (temporary == NULL)
	{
		*header = current;
	}
	else
	{
		while (temporary->nextn != NULL)
			temporary = temporary->nextn;
		temporary->nextn = current;
	}

	return (*header);
}

/**
 * free_command_line_list – This function frees a command_line_list
 * @header: header of the linked list.
 * Return: no return.
 */
void free_command_line_list(command_line_list **header)
{
	command_line_list *temporary;
	command_line_list *curr_ent;

	if (header != NULL)
	{
		curr_ent = *header;
		while ((temporary = curr_ent) != NULL)
		{
			curr_ent = curr_ent->nextn;
			free(temporary);
		}
		*header = NULL;
	}
}
