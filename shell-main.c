#include "shell.h"
#include <sys/wait.h>

int exec(int argc, char *argv[], char *envp[]);
char **format_line(char *line);

int main(int argc, char *argv[], char *envp[])
{
	int cont = 1;
	char *linebuf = NULL, **line;
	ssize_t l;
	size_t n = 0;

	printf("the number of args: %d\n", argc);
	while (cont == 1)
	{
		printf("\n$>");/*change to prompt()*/
		l = getline(&linebuf, &n, stdin);
		if (linebuf != NULL)
			printf("the linebuf is :\n %s----\n", linebuf);
		printf("past printing linebuf l == %ld\n", l);
		if (linebuf == NULL || l == -1)
			exit(1);
		printf("past checking if linebuf is null\n");
		if (linebuf != NULL)/*here is where it fails apparently*/
		{
			printf("linebuf is not null");
			if (linebuf[0] == 0)
				cont = 0; /*change to check builtins*/
		}
		printf("right before format line");
		line = format_line(linebuf);
		printf("%s----\n", (linebuf != NULL) ? linebuf : "linebuf is null");
		printf("%s %s\n", line[0], line[1]);
		exec(3, line, envp);
		free(line);
		free(linebuf);;
		n = 0;
	}
	printf("\n");
	return (0);
}

char **format_line(char *line)
{
	int len, i, numtokens = 0;
	char **newline;
	char *token;

	if (line == NULL)
		return (NULL);
	printf("line not null");
	for (len = 0; line[len] != '\n'; len++)
	{
		if (line[len] == ' ')
			numtokens++;
	}
	line[len] = 0;
	newline = malloc(sizeof(char *) * (numtokens + 2));
	newline[0] = strtok(line, " ");
	printf("the strtoks are:\n");
	for (i = 1; i < numtokens + 1; i++)
	{
		
		newline[i] = strtok(NULL, " ");
		printf("%s\n", newline[i]);
	}
	newline[i] = NULL;
	return (newline);
}

int exec(int argc, char *argv[], char *envp[])
{
	pid_t pid;
	int i = 0;

	printf("in exec: %s\n", argv[0]);
	if ((pid = fork()) == -1)
		perror("fork error");
	else if (pid == 0)
	{
		printf("into the child\n");
		execve(argv[0], argv, envp);
		printf("Return not expected, execve error\n");
	}
	wait(&pid);
	printf("\n");
	return (0);
}
