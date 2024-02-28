#include "thomas_shellby.h"

/**
 * _strdup – This is a function that duplicates a string in the heap memory.
 * @shellby_string: This is a char data type pointer string
 * Return: duplicated string
 */
char *_strdup(const char *shellby_string)
{
	char *current;
	size_t length;

	length = _strlen(shellby_string);
	current = malloc(sizeof(char) * (length + 1));
	if (current == NULL)
		return (NULL);
	_memcpy(current, shellby_string, length + 1);
	return (current);
}

/**
 * _strlen – This is a function that displays the length of a string.
 * @shellby_string: This is a char data type pointer string
 * Return: Always 0.
 */
int _strlen(const char *shellby_string)
{
	int length;

	for (length = 0; shellby_string[length] != 0; length++)
	{
	}
	return (length);
}

/**
 * cmp_chars – This is a function that compares various characters of strings
 * @stringy: This is the variable for the input string.
 * @delimiter: This is the delimiter declared in the header file.
 *
 * Return: 1 if are equals, 0 if not.
 */
int cmp_chars(char stringy[], const char *delimiter)
{
	unsigned int i, j_shellby, k_shellby;

	for (i = 0, k_shellby = 0; stringy[i]; i++)
	{
		for (j_shellby = 0; delimiter[j_shellby]; j_shellby++)
		{
			if (stringy[i] == delimiter[j_shellby])
			{
				k_shellby++;
				break;
			}
		}
	}
	if (i == k_shellby)
		return (1);
	return (0);
}

/**
 * _strtok – This is a function that tokenizes a string by a specified delimiter.
 * @stringy: This is our input string.
 * @delimiter: This is the variable store for our delimiter.
 *
 * Return: string splitted.
 */
char *_strtok(char stringy[], const char *delimiter)
{
	static char *splitted, *stringy_end;
	char *stringy_start;
	unsigned int i, bool;

	if (stringy != NULL)
	{
		if (cmp_chars(stringy, delimiter))
			return (NULL);
		splitted = stringy; /*Here we store the first address*/
		i = _strlen(stringy);
		stringy_end = &stringy[i]; /*Here we store the last address*/
	}
	stringy_start = splitted;
	if (stringy_start == stringy_end) /*Here we are reaching the end of the string*/
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		/*We are now breaking the loop to find the next token*/
		if (splitted != stringy_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		/*Here we are replacing the delimiter for a null character*/
		for (i = 0; delimiter[i]; i++)
		{
			if (*splitted == delimiter[i])
			{
				*splitted = '\0';
				if (splitted == stringy_start)
					stringy_start++;
				break;
			}
		}
		if (bool == 0 && *splitted) /*Now our value Stringy != Delimter*/
			bool = 1;
	}
	if (bool == 0) /*Now our value Stringy == Delimiter*/
		return (NULL);
	return (stringy_start);
}

/**
 * _isdigit – This is a function that determines if the string passed is a number
 *
 * @shellby_string: This is the variable call for our input string
 * Return: 1 if string is a number. 0 in other case.
 */
int _isdigit(const char *shellby_string)
{
	unsigned int i;

	for (i = 0; shellby_string[i]; i++)
	{
		if (shellby_string[i] < 48 || shellby_string[i] > 57)
			return (0);
	}
	return (1);
}
