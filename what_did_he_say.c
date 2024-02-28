#include "thomas_shellby.h"

/*
 * This is the program that will read user commands inputed into the prompt
 * @read_er is a previously defined function called in the header file
 * @fgets is used to get user input commands
 * @feof is used to specify what comes at the end of file
 * @i_print is a previously defined function called in the header file
 */

void read_er(char *user_input, size_t volume)
{
	if (fgets(user_input, volume, stdin) == NULL)
	{
		if (feof(stdin))
		{
			i_print("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			i_print("I didnt get that.\n");
			exit(EXIT_FAILURE);
		}
	}
	user_input[strcspn(user_input, "\n")] = '\0';
}
