#include "thomas_shellby.h"

/**
 * _memcpy – This function copies information between various void pointers in shellby.
 * @current_shellby_ptr: This represents the destination pointer.
 * @shellby_tr: This represents the source pointer.
 * @size: This is the size of the current pointer.
 *
 * Return: no return.
 */
void _memcpy(void *current_shellby_ptr, const void *shellby_tr, unsigned int size)
{
	char *char_shellby_tr = (char *)shellby_tr;
	char *char_current_shellby_ptr = (char *)current_shellby_ptr;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_current_shellby_ptr[i] = char_shellby_tr[i];
}

/**
 * _realloc – This function reallocates a memory block.
 * @shellby_tr: This is the pointer to the memory previously allocated.
 * @previous_size: This is the size, in bytes, of the allocated space of shellby_tr.
 * @current_size: This is the current size, in bytes, of the current memory block.
 *
 * Return: shellby_tr.
 * if current_size == previous_size, returns shellby_tr without changes.
 * if malloc fails, returns NULL.
 */
void *_realloc(void *shellby_tr, unsigned int previous_size, unsigned int current_size)
{
	void *current_shellby_ptr;

	if (shellby_tr == NULL)
		return (malloc(current_size));

	if (current_size == 0)
	{
		free(shellby_tr);
		return (NULL);
	}

	if (current_size == previous_size)
		return (shellby_tr);

	current_shellby_ptr = malloc(current_size);
	if (current_shellby_ptr == NULL)
		return (NULL);

	if (current_size < previous_size)
		_memcpy(current_shellby_ptr, shellby_tr, current_size);
	else
		_memcpy(current_shellby_ptr, shellby_tr, previous_size);

	free(shellby_tr);
	return (current_shellby_ptr);
}

/**
 * _reallocdp – This function reallocates a memory block of a double pointer in Shellby.
 * @shellby_tr: This is the double pointer to the memory previously allocated.
 * @previous_size: This is the size, in bytes, of the allocated space of shellby_tr.
 * @current_size: This is the current size, in bytes, of the current memory block.
 *
 * Return: shellby_tr.
 * if current_size == previous_size, returns shellby_tr without changing any values.
 * if malloc fails, returns NULL.
 */
char **_reallocdp(char **shellby_tr, unsigned int previous_size, unsigned int current_size)
{
	char **current_shellby_ptr;
	unsigned int i;

	if (shellby_tr == NULL)
		return (malloc(sizeof(char *) * current_size));

	if (current_size == previous_size)
		return (shellby_tr);

	current_shellby_ptr = malloc(sizeof(char *) * current_size);
	if (current_shellby_ptr == NULL)
		return (NULL);

	for (i = 0; i < previous_size; i++)
		current_shellby_ptr[i] = shellby_tr[i];

	free(shellby_tr);

	return (current_shellby_ptr);
}
