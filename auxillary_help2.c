#include "thomas_shellby.h"

/**
 * auxillary_help - Help information for the builtin help.
 * Return: no return
 */
void auxillary_help(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}
/**
 * auxillary_help_alias - Help information for the builtin alias.
 * Return: no return
 */
void auxillary_help_alias(void)
{
	char *help = "alias: alias [-p] [known_name[=value]...]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, _strlen(help));
}
/**
 * auxillary_help_change_dir - Help information for the builtin alias.
 * Return: no return
 */
void auxillary_help_change_dir(void)
{
	char *help = "change_dir: change_dir [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, _strlen(help));
}
