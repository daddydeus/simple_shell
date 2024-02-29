#include "thomas_shellby.h"

/**
 * free_shellby_data – This is the main Thomas Shellby function that frees the shellby_data structure
 * @shellby_data_store: This is the storehouse for all our shellby_data structure
 * Return: no return
 */
void free_shellby_data(data_in_shellby *shellby_data_store)
{
	unsigned int i;

	for (i = 0; shellby_data_store->_environment[i]; i++)
	{
		free(shellby_data_store->_environment[i]);
	}

	free(shellby_data_store->_environment);
	free(shellby_data_store->shellby_pid);
}

/**
 * set_shellby_data – This is the function that initializes the shellby_data structure
 * @shellby_data_store: This is the store file that houses the shellby_data structure
 * @argument_vect: This is our argument vector
 * Return: no return
 */
void set_shellby_data(data_in_shellby *shellby_data_store, char **argument_vect)
{
	unsigned int i;

	shellby_data_store->argument_vect = argument_vect;
	shellby_data_store->user_input = NULL;
	shellby_data_store->arguments = NULL;
	shellby_data_store->last_status = 0;
	shellby_data_store->count = 1;

	for (i = 0; environment[i]; i++)
		;

	shellby_data_store->_environment = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environment[i]; i++)
	{
		shellby_data_store->_environment[i] = _strdup(environment[i]);
	}

	shellby_data_store->_environment[i] = NULL;
	shellby_data_store->shellby_pid = last_status_itoa(getpid());
}

/**
 * main – This is the main entry point for our Thomas Shellby program
 * @argument_count: This is the argument count
 * @argument_vect: This is the argument vector
 * Return: 0 on success.
 */
int main(int argument_count, char **argument_vect)
{
	data_in_shellby shellby_data_store;
	(void) argument_count;

	signal(SIGNED_INT, get_signed_int);
	set_shellby_data(&shellby_data_store, argument_vect);
	shell_loop(&shellby_data_store);
	free_shellby_data(&shellby_data_store);
	if (shellby_data_store.last_status < 0)
		return (255);
	return (shellby_data_store.last_status);
}
