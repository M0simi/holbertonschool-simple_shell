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
char *path_env = NULL; /* this will store the PATH value from the environment */
char *path_copy, *dir; /* used to split the PATH string */
char full_path[1024];  /* buffer to build full paths like /bin/ls */
int i = 0;

/* search PATH manually inside environ */

while (environ[i])
{
if (strncmp(environ[i], "PATH=", 5) == 0)
{
path_env = environ[i] + 5; /* skip the "PATH=" part and keep the value */
break;
}
i++;
}

/* If PATH is not found, we can't continue */
if (!path_env)
return (NULL);

/* Make a copy of the PATH variable so we can safely modify it */
path_copy = strdup(path_env);
dir = strtok(path_copy, ":"); /* split PATH using ':' as the delimiter */

/* Go through each directory in PATH */
while (dir)
{
	sprintf(full_path, "%s/%s", dir, command); /* Build a potential full path by adding the command name */
/* Check if this path points to an executable file */
	if (access(full_path, X_OK) == 0)
	{
		free(path_copy);
		return (strdup(full_path));
	}
	dir = strtok(NULL, ":"); /* Move to the next directory in PATH */
}

/* Command was not found, clean up and return NULL */
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
	/* PATH was not found */
	return (0);
}
