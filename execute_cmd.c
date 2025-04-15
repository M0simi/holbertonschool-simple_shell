#include "shell.h"

/**
 * execute_cmd - Executes a command with PATH handling
 * @args: Argument vector
 */
void execute_cmd(char **args)
{
pid_t pid;
int status;
char *cmd_path;

if (args[0] == NULL)
return;


if (strcmp(args[0], "env") == 0)
{
int i = 0;
while (environ[i])
{
printf("%s\n", environ[i]);
i++;
}
return;
}

/* make sure of the command */
if (access(args[0], X_OK) == 0)
{
cmd_path = strdup(args[0]);
}
else
{
cmd_path = find_command(args[0]);
if (cmd_path == NULL)
{
fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
exit(127);
}
}

pid = fork();

if (pid == 0)
{
if (execve(cmd_path, args, environ) == -1)
{
fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
free(cmd_path);
exit(127);
}
}
else if (pid < 0)
{
perror("fork");
}
else
{
waitpid(pid, &status, 0);
free(cmd_path);
if (WIFEXITED(status))
exit(WEXITSTATUS(status));
}
}
