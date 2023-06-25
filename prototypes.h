#ifndef P_H
#define P_H
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#define MAX_COMMAND 100

#define GNU_SOURCE
#define BUFFER_LEN 1024

int isatty(int fd);
extern char **environ;
int main(int argc, char **argv, char **env);
int _strlen(char *s);
int execute(char **argv);
char *_getline(void);
char **tokenize(char *ptr, int bufsize);
void *reallocate(void *str, unsigned int size1, unsigned int size2);
char *locate_command(char *argv);
char *_searchenv(char *env);
char *_strconcat(char *s1, char *s2);
int search_builtin(char *argv);
void exec_builtins(char **argv, int k);
void _exit_(char **argv);
int _atoi(char *s);
int _strcmp(char *s1, char *s2);
#endif
