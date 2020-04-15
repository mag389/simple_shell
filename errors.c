#include "shell.h"

/**
* _atoi - takes a number array and returns the int value if it exists
* Return: the integer number, 0 for failure
* @str: the string containing the number
*/
int _atoi(char *str)
{
	int ret = 0, len, i;

	for (len = 0; str[len] != 0; len++)
		if (str[len] < '0' || str[len] > '9')
			return (0);
	for (i = 0; i < len; i++)
		ret = ret * 10 + (str[i] - '0');
	return (ret);
}

/**
* _itoa - integer to array
* Return: char pointer to array containing char representation of the int
* @num: the number to be represented
*/
char *_itoa(int num)
{
	char *arr;
	int cpy = num, size;

	for (size = 1; size < 15; size++)
	{
		cpy /= 10;
		if (cpy == 0)
			break;
	}
	arr = malloc(size + 1);
	if (!arr)
		return (NULL);
	arr[size] = 0;
	for (size--; size >= 0; size--)
	{
		arr[size] = '0' + num % 10;
		num /= 10;
	}
	return (arr);
}

/**
* print_error - prints error messages
* Return: void
* @cont: the loop num
* @arg: the given command
* @errno: the err number
*/
void print_error(int cont, char *arg, int errno)
{
	char *conta;

	conta = _itoa(cont);

	write(2, "hsh: ", 5);
	if (conta)
	{
	write(2, conta, _strlen(conta));
	free(conta);
	}
	write(2, ": ", 2);
	write(2, arg, _strlen(arg));
	if (errno == 0)
		write(2, ": not found\n", 12);
	else
		write(2, "\n", 1);
}
