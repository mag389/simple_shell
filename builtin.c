#include "shell.h"
int _strcmp(char *str1, char *str2);
void built_exit(char **line, int *cont);
void built_env(char **line, int *cont);
/**
* builtin - checks for builtins, executes upon finding
* Return: 1 if a function was found and run, otherwise 0
* @line: the command to search for line[0] is the exec file
* @cont: whether the loop should continue
*/
int builtin(char **line, int *cont)
{
/*	printf("checking builtin\n");*/
	if (line == NULL || line[0] == NULL)
		return (0);
/*	printf("line and line[0] not null\n");*/
/*	printf("line[0] is: %s\n", line[0]);*/
	if (_strcmp(line[0], "exit") == 1)
	{
/*		printf("it did match exit\n");*/
		built_exit(line, cont);
		return (1);
	}
	if (_strcmp(line[0], "env") == 1)
	{
/*		printf("it did match env\n");*/
		built_env(line, cont);
		return (1);
	}
	return (0);
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

/*	printf("printinf env:\n");*/
	for (p = environ; *p; p++)
	{
		for (len = 0; (*p)[len];)
			len++;
		write(1, *p, len);
		write(1, "\n", 1);
/*		printf ("%s\n", *p);*/
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
	*cont = 0;
/*	printf("just changed cont to %d\n", cont[0]);*/
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

/*	printf("comparing two string\n");*/
	for (i = 0; str1[i] != 0 && str2[i] != 0; i++)
	{
		if (str1[i] != str2[i])
			return (0);
	}
/*	printf("they match\n");*/
	return (1);
}
