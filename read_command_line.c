#include "thomas_shellby.h"

/**
 * read_command_line – This is the function that reads the input string from the command line.
 * @i_eof: This returns the value of the getline function
 * Return: input string
 */
char *read_command_line(int *i_eof)
{
	char *user_input = NULL;
	size_t buffersize = 0;

	*i_eof = getline(&user_input, &buffersize, stdin);

	return (user_input);
}
