#include "shell.h"
int _strcmp(char *str1, char *str2);
void built_exit(char **line, int *cont);
void built_env(char **line, int *cont);
void built_help(char **line, int *cont);
/**
* builtin - checks for builtins, executes upon finding
* Return: 1 if a function was found and run, otherwise 0
* @line: the command to search for line[0] is the exec file
* @cont: whether the loop should continue
*/
int builtin(char **line, int *cont)
{
	if (line == NULL || line[0] == NULL)
		return (1);
	if (_strcmp(line[0], "exit") == 1)
	{
		built_exit(line, cont);
		return (1);
	}
	if (_strcmp(line[0], "env") == 1)
	{
		built_env(line, cont);
		return (1);
	}
	if (_strcmp(line[0], "help") == 1)
	{
		built_help(line, cont);
		return (1);
	}
	return (0);
}
/**
* built_help - the help builtin
* Return: void
* @line: the given command for help
* @cont: loop check variable to change
*/
void built_help(char **line, int *cont)
{
	(void)cont;

	if (!line[1])
	{
		write(1, "Usage: help [BUILTIN]\n", 22);
	}
	else if (_strcmp(line[1], "exit") == 1)
		write(1, "exits the shell, takes integer argument as exit code\n", 53);
	else if (_strcmp(line[1], "env") == 1)
		write(1, "prints the entire current environment\n", 38);
	else if (_strcmp(line[1], "help") == 1)
		write(1, "return info about builtin commands\n", 35);
	else if (_strcmp(line[1], "list") == 1)
		write(1, "builtin commands: exit, env, help, list\n", 40);
	else
		write(1, "command not recognized, try list to see builtin commands\n", 57);
}
/**
* built_env - the env builtin, prints env
* Return: void
* @line: the given command for exit with args
* @cont: loop check variable to change
*/
void built_env(char **line, int *cont)
{
	char **p;
	int len;

	(void)line;
	(void)cont;

	for (p = environ; *p; p++)
	{
		for (len = 0; (*p)[len];)
			len++;
		write(1, *p, len);
		write(1, "\n", 1);
	}
}

/**
* built_exit - changes values to exit shell
* Return: void
* @line: the given command for exit with args
* @cont: loop check variable to change
*/
void built_exit(char **line, int *cont)
{
	(void)line;
/*	change void line when we put in args*/
	*cont *= -1;
	if (line[1])
		ex_status = _atoi(line[1]) % 256;
}

/**
* _strcmp - compare two string
* Return: 1 for match, 0 for not
* @str1: the first string
* @str2: the secomd string
*/
int _strcmp(char *str1, char *str2)
{
	int i;

	for (i = 0; str1[i] != 0 && str2[i] != 0; i++)
	{
		if (str1[i] != str2[i])
			return (0);
	}
	if (str1[i] != str2[i])
		return (0);
	return (1);
}
