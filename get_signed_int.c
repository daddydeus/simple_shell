#include "thomas_shellby.h"

/**
 * get_signed_int – This is a function that handles the crtl + c call in the prompt
 * @signed_i: This is our signal handler variable
 */
void get_signed_int(int signed_i)
{
	(void)signed_i;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
