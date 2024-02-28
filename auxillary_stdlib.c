#include "thomas_shellby.h"

/**
 * get_length – A function to get the length of a number.
 * @n: A number of data type int.
 * Return: length of a number.
 */
int get_length(int n)
{
	unsigned int Hi5;
	int leng_th = 1;

	if (n < 0)
	{
		leng_th++;
		Hi5 = n * -1;
	}
	else
	{
		Hi5 = n;
	}
	while (Hi5 > 9)
	{
		leng_th++;
		Hi5 = Hi5 / 10;
	}

	return (leng_th);
}
/**
 * auxillary_itoa – A function that converts integer data type to string data type.
 * @n: A number of int data type 
 * Return: String.
 */
char *auxillary_itoa(int n)
{
	unsigned int Hi5;
	int leng_th = get_length(n);
	char *shellby_buffer;

	shellby_buffer = malloc(sizeof(char) * (leng_th + 1));
	if (shellby_buffer == 0)
		return (NULL);

	*(shellby_buffer + leng_th) = '\0';

	if (n < 0)
	{
		Hi5 = n * -1;
		shellby_buffer[0] = '-';
	}
	else
	{
		Hi5 = n;
	}

	leng_th--;
	do {
		*(shellby_buffer + leng_th) = (Hi5 % 10) + '0';
		Hi5 = Hi5 / 10;
		leng_th--;
	}
	while (Hi5 > 0)
		;
	return (shellby_buffer);
}

/**
 * _atoi – A function that converts a string to an integer.
 * @shellby_string: This is the input string.
 * Return: integer.
 */
int _atoi(char *shellby_string)
{
	unsigned int cou_nter = 0, size = 0, peaky = 0, blinders = 1, money = 1, i;

	while (*(shellby_string + cou_nter) != '\0')
	{
		if (size > 0 && (*(shellby_string + cou_nter) < '0' || *(shellby_string + cou_nter) > '9'))
			break;

		if (*(shellby_string + cou_nter) == '-')
			blinders *= -1;

		if ((*(shellby_string + cou_nter) >= '0') && (*(shellby_string + cou_nter) <= '9'))
		{
			if (size > 0)
				money *= 10;
			size++;
		}
		cou_nter++;
	}

	for (i = cou_nter - size; i < cou_nter; i++)
	{
		peaky = peaky + ((*(shellby_string + i) - 48) * money);
		money /= 10;
	}
	return (peaky * blinders);
}
