#include "shell.h"

/**
 * execute_cmd - Executes a command
 * @args: Arguments passed to the shell
 */
void execute_cmd(char **args)
{
pid_t pid;
int status;

if (strcmp(args[0], "exit") == 0)
exit(0);
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

pid = fork();
if (pid == 0)
{
if (execvp(args[0], args) == -1)
{
perror("hsh");
exit(EXIT_FAILURE);
}
}
else if (pid < 0)
perror("fork");
else
waitpid(pid, &status, 0);
}
