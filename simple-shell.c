#include "shell.h"
/**
* main - runs the shell
* Return: 0
* @argc: number of arguments
* @argv: the list of arguments
* @envp: the environment
*/
int main(int argc, char *argv[], char *envp[])
{
	int cont = 1, built, execi;
	char *linebuf = NULL, **line;
	ssize_t l;
	size_t n = 0;

	ex_status = 0;
	signal(2, SIG_IGN);/*uncomment to disable quitting with ^C*/
	(void)argv;
	(void)argc;/* only will be used later*/
	while (cont++ > 0)
	{
		if (isatty(STDIN_FILENO))
			write(1, "$ ", 2);
		l = getline(&linebuf, &n, stdin);/* change stdin if it's a file*/
		if (l == -1)
		{
			free(linebuf);
			exit(1);
		}
		line = format_line(linebuf);
		built = builtin(line, &cont);
/*		printf("cont is: %d\n", cont);*/
		execi = (built == 0) ? exec(3, line, envp) : 0;/* 3 is a placeholder*/
		free(line);
		free(linebuf);
		n = execi;
/*		printf("the pid is %ul \n", getpid());*/
/* can combine the free and n = 0 into function for space if needed */
	}
/*	write(1, "\n", 1); for testing purposes it helped to have*/
	if (ex_status > 0)
		exit(ex_status);
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

	if (linebuf == NULL)/*not sure if necesary, check if we can get passed null*/
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
	int p = 0;
	char *pathfile;

	(void)argc;
/*	if (argv[0] == NULL || argv[0] != NULL)*/
/*	{*/
	pathfile = check_path(argv[0], envp);
	if (pathfile)
		p = 1;
/*			return (0);  change to print something */
/*		printf("the pathfile in exec: %s\n", pathfile);*/
/*	}*/
	if ((access(argv[0], F_OK | X_OK) != 0 && p == 0) || argv[0][0] == '/')
		return (0);
	pid = fork();
	if (pid == -1)
		perror("fork error");
	else if (pid == 0)
	{
		if (p == 0)
		{
			printf("not path\n");
			execve(argv[0], argv, envp);
		}
		else
			execve(pathfile, argv, envp);
		write(1, "return not expected, exec error\n", 32);
/*		if (pathfile)*/
/*			free(pathfile);*/
/*		exit(1);*/
	}
	wait(&pid);
	if (p == 1)
		free(pathfile);
/*	write(1, "\n", 1); should we still print line on failure */
	return (0);
}
