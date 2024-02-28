#include "thomas_shellby.h"

/**
 * auxillary_help_environment – This displays the help manual for the builtin environment function
 * Return: no return
 */
void auxillary_help_environment(void)
{
	char *help = "environment: environment [option] [known_name=value] [command [arguments]]\n\t";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, help, _strlen(help));

}
/**
 * auxillary_help_setenvironment - Manual for the builtin setenvironment function
 * Return: no return
 */
void auxillary_help_setenvironment(void)
{

	char *help = "setenvironment: setenvironment (const char *known_name, const char *value,";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "int replace)\n\t";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, help, _strlen(help));
}
/**
 * auxillary_help_unsetenvironment - Manual for the builtin unsetenvironment function
 * Return: no return
 */
void auxillary_help_unsetenvironment(void)
{
	char *help = "unsetenvironment: unsetenvironment (const char *known_name)\n\t";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, help, _strlen(help));
}


/**
 * auxillary_help_general – This is the entry point for the manual for the builtin help command
 * Return: no return
 */
void auxillary_help_general(void)
{
	char *help = "^-^ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "These commands are defined internally.Type 'help' to see the list";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "Type 'help known_name' to find out more about the function 'known_name'.\n\n ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = " alias: alias [known_name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "[dir]\nexit: exit [n]\n  environment: environment [option] [known_name=value] [command ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "[arguments]]\n  setenvironment: setenvironment [variable] [value]\n  unsetenvironment: ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "unsetenvironment [variable]\n";
	write(STDOUT_FILENO, help, _strlen(help));
}
/**
 * auxillary_help_exit – manual for the builint exit command
 * Return: no return
 */
void auxillary_help_exit(void)
{
	char *help = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "status is that of the last command executed\n";
	write(STDOUT_FILENO, help, _strlen(help));
}
