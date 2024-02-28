#include "thomas_shellby.h"

/*
 * This is the executable code that ac as an entty point for our shell.
 * @prompt_ly is the function that displays the prompt
 * @read_er is the function that reads user input
 * @execut_er is the function that executes user input commands
 */

int main(void)
{
	char user_input[256];
	while (true)
	{
		prompt_ly();
		read_er(user_input, sizeof(user_input));
		execut_er(user_input);
	}

	return 0;
}
