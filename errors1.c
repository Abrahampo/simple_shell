#include "shell.h"

/**
 * _erratoi - The string that converts an integer
 * @s: The converted string
 * Return: 0 if there's no numbers in the string that convert a number
 * -1 for errors or error
 */

int _erratoi(char *s)
{
	int k = 0;
	unsigned long int outcome = 0;

	if (*s == '+')
		s++;
	for (k = 0;  s[k] != '\0'; k++)
	{
		if (s[k] >= '0' && s[k] <= '9')
		{
			outcome *= 10;
			outcome += (s[k] - '0');
			if (outcome > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (outcome);
}

/**
 * print_error - The messages that prints errors
 * @info: parameter that returns info for structure
 * @estr: The type string that specify or that have an errors
 * Return: 0 if there is a numbers in string, or converted number
 *        -1 for errors
 */

void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - A function that prints integer number to base10
 * @input: for input
 * @fd: The filedescriptor
 * Return: The printed characters of number or number
 */

int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int k, check = 0;

	unsigned int aph_stat;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		aph_stat = -input;
		__putchar('-');
		check++;
	}
	else
		aph_stat = input;
	aph_stat = input;
	for (k = 1000000000; k > 1; k /= 10)
	{
		if (aph_stat / k)
		{
			__putchar('0' + aph_stat / k);
			check++;
		}
		aph_stat %= k;
	}
	__putchar('0' + aph_stat);
	check++;

	return (check);
}

/**
 * convert_number - for function converting, or clone for itoa
 * @num: The number or numbers
 * @base: The base or bases
 * @flags: flags for argument (s)
 * Return: the string
 */

char *convert_number(long int num, int base, int flags)
{
	static char *A;
	static char bb[50];
	char mm = 0;
	char *pointer;
	unsigned long number = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		number = -num;
		mm = '-';

	}
	A = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pointer = &bb[49];
	*pointer = '\0';

	do	{
		*--pointer = A[number % base];
		number /= base;
	} while (number != 0);

	if (mm)
		*--pointer = mm;
	return (pointer);
}

/**
 * remove_comments - A function that replace or delete comment to '#' with '\0'
 * @buf: A string that is use to modify the address
 * Return: just 0;
 */

void remove_comments(char *buf)
{
	int k;

	for (k = 0; buf[k] != '\0'; k++)
		if (buf[k] == '#' && (!k || buf[k - 1] == ' '))
		{
			buf[k] = '\0';
			break;
		}
}
