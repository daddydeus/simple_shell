#include "thomas_shellby.h"

/**
 * _strcat – This is a function that integrates two strings
 * @destination: This is the pointer of char data type to the destination of the copied stringy
 * @string_rc: This is the pointer of const char data type to the source of stringy
 * Return: the destination
 */
char *_strcat(char *destination, const char *string_rc)
{
	int i;
	int j_shellby;

	for (i = 0; destination[i] != '\0'; i++)
		;

	for (j_shellby = 0; string_rc[j_shellby] != '\0'; j_shellby++)
	{
		destination[i] = string_rc[j_shellby];
		i++;
	}

	destination[i] = '\0';
	return (destination);
}
/**
 * *_strcpy – This is a function that copies the string pointed to by string_rc.
 * @destination: This is a pointer of char data type that points the destination of the copied string_rc
 * @string_rc: This is a pointer of char data type and is the source of string_rc
 * Return: the destination.
 */
char *_strcpy(char *destination, char *string_rc)
{

	size_t a;

	for (a = 0; string_rc[a] != '\0'; a++)
	{
		destination[a] = string_rc[a];
	}
	destination[a] = '\0';

	return (destination);
}
/**
 * _strcmp – This is a function that compares two strings in shellby.
 * @string1: This is a first entry of type string_rc to be compared
 * @string2: This is a second entry of type string_rc to be compared
 * Return: Always 0.
 */
int _strcmp(char *string1, char *string2)
{
	int i;

	for (i = 0; string1[i] == string2[i] && string1[i]; i++)
		;

	if (string1[i] > string2[i])
		return (1);
	if (string1[i] < string2[i])
		return (-1);
	return (0);
}
/**
 * _strchr – This is a function that locates a character in a string in shellby,
 * @shellby_string: This is simply a string entry.
 * @c: This is simply a character.
 * Return: the pointer to the first occurrence of the character c.
 */
char *_strchr(char *shellby_string, char c)
{
	unsigned int i = 0;

	for (; *(shellby_string + i) != '\0'; i++)
		if (*(shellby_string + i) == c)
			return (shellby_string + i);
	if (*(shellby_string + i) == c)
		return (shellby_string + i);
	return ('\0');
}
/**
 * _strspn – This is a function that finds the length of a substring prefix.
 * @shellby_string: This is the initial string segment.
 * @accepted: These are the accepted bytes in shellby.
 * Return: the number of accepted bytes.
 */
int _strspn(char *shellby_string, char *accepted)
{
	int i, j_shellby, bool;

	for (i = 0; *(shellby_string + i) != '\0'; i++)
	{
		bool = 1;
		for (j_shellby = 0; *(accepted + j_shellby) != '\0'; j_shellby++)
		{
			if (*(shellby_string + i) == *(accepted + j_shellby))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (i);
}
