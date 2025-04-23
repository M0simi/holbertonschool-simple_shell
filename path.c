#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

/**
 * find_command - finds the path of a given command
 * @command: the command to search for
 *
 * Return: the full path to the command, or NULL if not found
 */
char *find_command(char *command)
{
char *path_env = NULL;
char *path_copy, *dir;
char full_path[1024];
int i = 0;

/* search PATH manually inside environ */

while (environ[i])
{
if (strncmp(environ[i], "PATH=", 5) == 0)
{
path_env = environ[i] + 5;
break;
}
i++;
}

if (!path_env)
return (NULL);

path_copy = strdup(path_env);
dir = strtok(path_copy, ":");

while (dir)
{
        /* Allocate memory for full_path dynamically */
        full_path = malloc(strlen(dir) + strlen(command) + 2); /* 1 for '/' and 1 for null terminator */
        if (!full_path)
        {
            free(path_copy);
            return (NULL); /* Handle memory allocation failure */
        }
sprintf(full_path, "%s/%s", dir, command);
if (access(full_path, X_OK) == 0)
{
free(path_copy);
return (full_path);
}
free(full_path);
dir = strtok(NULL, ":");
}

free(path_copy);
return (NULL);
}




/**
 * has_path_env - Checks if the PATH variable is present in the environment
 *
 * Return: 1 if PATH is found, 0 otherwise
 */

int has_path_env(void)
{
	int i = 0;

	while (environ[i])
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
			return (1);
		i++;
	}
	return (0);
}
