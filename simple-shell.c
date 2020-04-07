#include "shell.h"

int exec(int argc, char *argv[], char *envp[]);
char **format_line(char *linebuf);
/**
* main - runs the shell
* Return: 0
* @argc: number of arguments
* @argv: the list of arguments
* @envp: the environment
*/
int main(int argc, char *argv[], char *envp[])
{
	int cont = 1;
	char *linebuf = NULL, **line;
	ssize_t l;
	size_t n = 0;

	(void)argv;
	(void)argc;/* only will be used later*/
	while (cont == 1)
	{
		write(1, "$", 1);
		l = getline(&linebuf, &n, stdin);/* change stdin if it's a file*/
		if (l == -1)
			exit(1);/*we need to change this to have it free stuff*/
		line = format_line(linebuf);
		if (linebuf[0] == 0)/*current standin for exit function*/
			cont = 0;
	/*	builtin(line); if it gets a builtin it should skip the non bultin */
	/*	get_path(line); can either return an allocated string, or change
				the first part of the line doubke pointer */
		exec(3, line, envp);/* 3 is currently just a placeholder*/
		free(line);
		free(linebuf);
		n = 0;
	/* we can combine the free and n = 0 into one subfunction for space if needed */
	}
/*	write(1, "\n", 1); for testing purposes it helped to have*/
	return (0);
}
/**
* format_line - formats the linebuf for execution
* Return: a double pointer to the linebuf after tokenization
* @linebuf: a newline terminated string, from getline call
*/
char **format_line(char *linebuf)
{
	int len, i, numtokens = 0;
	char **newline;
/*	char *token; may be used later, as of now not*/

	if (linebuf == NULL)/*not sure if necesary, check later if we can get passed null*/
		return (NULL);
	for (len = 0; linebuf[len] != '\n'; len++)/*came from getline so ends on \n*/
	{
		if (linebuf[len] == ' ')
			numtokens++;
	}
	linebuf[len] = 0; /*end it with a null, instead of \n */
	newline = malloc(sizeof(char *) * (numtokens + 2));
	newline[0] = strtok(linebuf, " ");
	for (i = 1; i < numtokens + 1; i++)
	{
		newline[i] = strtok(NULL, " ");
	}
	newline[i] = NULL;/*the pointer must also be null terminated */
	return (newline);
}

/**
* exec - executes the given program
* Return: 0, subject to change based on failure
* @argc: a placehoder variable for later use
* @argv: the arguments to use for the program called
* @envp: the environment being run in
*/
int exec(int argc, char *argv[], char *envp[])
{
	pid_t pid;
/*	int i = 0;may be used later*/

	(void)argc;
	pid = fork();
	if (pid == -1)
		perror("fork error");
	else if (pid == 0)
	{
		execve(argv[0], argv, envp);
		write(1, "return not expected, exec error\n", 32);
	}
	wait(&pid);
/*	write(1, "\n", 1); should we still print line on failure */
	return (0);
}
