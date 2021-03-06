#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <string.h>
#include <stdarg.h>
#include <fcntl.h>
#include <dirent.h>

/* simple shell */
int exec(int argc, char *argv[], char *envp[]);
char **format_line(char *linebuf);
int _isdir(char *name);
/* path file */
char *check_path(char *file, char *envp[]);
char *get_env(char *var, char *envp[]);
int _strlen(char *str);
char *path_concat(char *path, char *file);
/* builtins */
int builtin(char **line, int *cont);
int _strcmp(char *str1, char *str2);
void built_exit(char **line, int *cont);
void built_env(char **line, int *cont);
/* errors */
int _atoi(char *str);
char *_itoa(int num);
void print_error(int cont, char *arg, int errno);
int _strchr(char *str, char c);
extern char **environ;
int ex_status;
#endif
