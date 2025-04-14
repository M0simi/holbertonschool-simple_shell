#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

char **parse_line(char *line);
void execute_cmd(char **args);
extern char **environ;

#endif
