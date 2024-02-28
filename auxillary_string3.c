#include "thomas_shellby.h"

/**
 * rev_string – This is a function that reverses a string.
 * @shellby_string: This is our input string.
 * Return: no return.
 */
void rev_string(char *shellby_string)
{
	int cou_nter = 0, i, j_shellby;
	char *stringy, temporary;

	while (cou_nter >= 0)
	{
		if (shellby_string[cou_nter] == '\0')
			break;
		cou_nter++;
	}
	stringy = shellby_string;

	for (i = 0; i < (cou_nter - 1); i++)
	{
		for (j_shellby = i + 1; j_shellby > 0; j_shellby--)
		{
			temporary = *(stringy + j_shellby);
			*(stringy + j_shellby) = *(stringy + (j_shellby - 1));
			*(stringy + (j_shellby - 1)) = temporary;
		}
	}
}
