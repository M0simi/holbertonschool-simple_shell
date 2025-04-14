#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

char *find_command(char *command)
{
char *path = getenv("PATH");
char *path_copy = strdup(path);
char *dir = strtok(path_copy, ":");
char full_path[1024];

while (dir)
{
sprintf(full_path, "%s/%s", dir, command);
if (access(full_path, X_OK) == 0)
{
free(path_copy);
return strdup(full_path);
}
dir = strtok(NULL, ":");
}

free(path_copy);
return NULL;
}
