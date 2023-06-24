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

#define MAX_COMMAND 100

#define GNU_SOURCE
#define BUFFER_LEN 1024

int isatty(int fd);
extern char **environ;
int main(int argc, char **argv, char **env);
int execute(char **argv);
char *_getline(void);
char **tokenize(char *ptr, int bufsize);
void *reallocate(void *str, unsigned int size1, unsigned int size2);

#endif
