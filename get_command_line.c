#include "thomas_shellby.h"

/**
 * bring_command_line – This is the function that assigns the command_line variable for get_command_line
 * @command_line_ptr: This is the buffer that stores the user_input string
 * @shellby_buffer: This is a string that is been called to the command_line
 * @n: This int defines the size of command_line
 * @j_shellby: This int defines the size of the shellby_buffer
 */
void bring_command_line(char **command_line_ptr, size_t *n, char *shellby_buffer, size_t j_shellby)
{

	if (*command_line_ptr == NULL)
	{
		if  (j_shellby > BUFFERSIZE)
			*n = j_shellby;

		else
			*n = BUFFERSIZE;
		*command_line_ptr = shellby_buffer;
	}
	else if (*n < j_shellby)
	{
		if (j_shellby > BUFFERSIZE)
			*n = j_shellby;
		else
			*n = BUFFERSIZE;
		*command_line_ptr = shellby_buffer;
	}
	else
	{
		_strcpy(*command_line_ptr, shellby_buffer);
		free(shellby_buffer);
	}
}
/**
 * get_command_line – This is the function that reads inputs from a data stream
 * @command_line_ptr: This is the buffer that stores the user_input
 * @n: This int defines the size of command_line_ptr
 * @stream: This int determines the stream to read from
 * Return: The number of bytes
 */
ssize_t get_command_line(char **command_line_ptr, size_t *n, FILE *stream)
{
	int i;
	static ssize_t user_input;
	ssize_t retval;
	char *shellby_buffer;
	char t = 'z';

	if (user_input == 0)
		fflush(stream);
	else
		return (-1);
	user_input = 0;

	shellby_buffer = malloc(sizeof(char) * BUFFERSIZE);
	if (shellby_buffer == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && user_input == 0))
		{
			free(shellby_buffer);
			return (-1);
		}
		if (i == 0 && user_input != 0)
		{
			user_input++;
			break;
		}
		if (user_input >= BUFFERSIZE)
			shellby_buffer = _realloc(shellby_buffer, user_input, user_input + 1);
		shellby_buffer[user_input] = t;
		user_input++;
	}
	shellby_buffer[user_input] = '\0';
	bring_command_line(command_line_ptr, n, shellby_buffer, user_input);
	retval = user_input;
	if (i != 0)
		user_input = 0;
	return (retval);
}
