#include "thomas_shellby.h"

/* 
 * Here is our custom made printf function that will be use to print to standard output
 * @write is the system call used here
 * To make sure that we dont have to keep making write functions and to simplify codee decided to write to the designated STDOUT_FILENO
 */

void i_print(const char *on_screen)
{
	write(STDOUT_FILENO, on_screen, strlen(on_screen));
}
