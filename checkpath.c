#include "shell.h"

/**
* check_path - checks the path for a given file
* Return: the full filename or NULL
* @file: the string filename without the path
* @envp: the environment containing the path
*/
char *check_path(char *file, char *envp[])
{
	char *path, *pathfile;
	int index, marker = 0, f = 0;

	path = get_env("PATH", envp);
/*	printf("the partial path is: %s\n", path);*/
	if (!file || !file[0])
		return (NULL);
	for (index = 0; path[index]; index++)
	{
		if (marker == 1)
		{
			f = 1;
			pathfile = path_concat(&path[index], file);
				if (access(pathfile, F_OK | X_OK) == 0)
				return (pathfile);
		}
		if (f == 1)
		{
			free(pathfile);
			f = 0;
		}
		marker = 0;
		if (path)
			if (path[index] == ':' || path[index] == '=')
				marker = 1;
	}
	return (NULL);
}
/**
* path_concat - concats the file with the next part of the path
* Return: the allocated new filename
* @path: the path, starting from after PATH=
* @file: the filename that might be there
*/
char *path_concat(char *path, char *file)
{
	int i, lenf, lenp;
	char *cat;

	lenf = _strlen(file);
	lenp = 0;
/*	printf("the lenf is: %d\n", lenf);*/
	while (path[lenp] != 0 && path[lenp] != ':')
		lenp++;
	cat = malloc(lenp + lenf + 2);
	if (cat == NULL)
		return (NULL);
	for (i = 0; i < lenp; i++)
		cat[i] = path[i];
	cat[i] = '/';
	for (i = 0; i < lenf; i++)
		cat[i + 1 + lenp] = file[i];
	cat[lenf + lenp + 1] = 0;
/*	printf("the full path is: %s\n", cat);*/
	return (cat);
}

/**
* get_env - get's the specified variable from the environment
* Return: the variable, or NULL
* @var: the variable from the environment you want
* @envp: the environment
*/
char *get_env(char *var, char *envp[])
{
	int i, j;

	if (var == NULL || envp == NULL)
		return (NULL);
	for (i = 0; envp[i]; i++)
	{
		for (j = 0; var[j] == envp[i][j]; j++)
		{
		}
		if (var[j] == 0 && envp[i][j] == '=')
			return (envp[i]);
	}
	return (NULL);
}
/**
* _strlen - gets length of a string
* Return: the length of the string
* @str: the string
*/
int _strlen(char *str)
{
	int len = 0;

	if (str == NULL)
		return (0);
	while (str[len])
		len++;
	return (len);
}
