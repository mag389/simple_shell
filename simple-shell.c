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
	signal(2, SIG_IGN);
	(void)argv;
	(void)argc;
	while (cont > 0)
	{
		if (isatty(STDIN_FILENO))
			write(1, "$ ", 2);
		l = getline(&linebuf, &n, stdin);
		if (l == -1)
		{
			free(linebuf);
			exit(0);
		}
		line = format_line(linebuf);
		built = builtin(line, &cont);
		execi = (built == 0) ? exec(cont, line, envp) : 0;
		free(line);
		free(linebuf);
		n = execi;
		cont++;
	}
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

	if (linebuf == NULL)
		return (NULL);
	for (len = 0; linebuf[len] != '\n'; len++)
	{
		if (linebuf[len] == ' ')
			numtokens++;
		if (linebuf[len] == '#')
		{
			if (len == 0)
				linebuf[len] = '\0';
			else if (linebuf[len - 1] == ' ')
				linebuf[len] = '\0';
		}
	}
	linebuf[len] = 0;
	newline = malloc(sizeof(char *) * (numtokens + 2));
	newline[0] = strtok(linebuf, " \n\v\r\a\t");
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

	pathfile = check_path(argv[0], envp);
	if (pathfile)
		p = 1;
	if ((access(argv[0], F_OK) != 0 && p == 0))
	{
		print_error(argc, argv[0], 0);
		return (0);
	}
	if ((access(argv[0], F_OK | X_OK) != 0 && p == 0))
	{
		print_error(argc, argv[0], 1);
		return (0);
	}
	if (p == 0 && _isdir(argv[0]) == 1)
	{
		print_error(argc, argv[0], 1);
		return (0);
	}
	pid = fork();
	if (pid == -1)
		perror("fork error");
	else if (pid == 0)
	{
		if (p == 0)
		{
			execve(argv[0], argv, envp);
		}
		else
			execve(pathfile, argv, envp);
		write(2, "return not expected, exec error\n", 32);
	}
	wait(&pid);
	if (p == 1)
		free(pathfile);
	return (0);
}
/**
* _isdir - checks id the directory exists
* Return: 1 if it does, else 0
* @name: the name of the possible directory
*/
int _isdir(char *name)
{
	DIR *dir;

	dir = opendir(name);
	if (dir == NULL)
		return (0);
	free(dir);
	return (1);
}
