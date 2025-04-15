#include "shell.h"

/**
 * execute_cmd - Executes a command with path resolution
 * @args: Argument vector (command and its arguments)
 */
void execute_cmd(char **args)
{
	pid_t pid;
	int status;
	char *cmd_path;

	if (args[0] == NULL)
		return;

	/* Handle built-in 'exit' */
	if (strcmp(args[0], "exit") == 0)
		exit(0);

	/* Handle built-in 'env' */
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

	/* Check if command is directly executable or resolve from PATH */
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
			return;
		}
	}

	/* Fork and execute */
	pid = fork();

	if (pid == 0)
	{
		/* Child process */
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
		/* Parent process */
		waitpid(pid, &status, 0);
		free(cmd_path);
	}
}
