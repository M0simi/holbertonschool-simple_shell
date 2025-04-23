#include "shell.h"

/**
 * handle_builtins - Checks and executes built-in commands
 * @args: Argument vector
 * Return: 1 if built-in was handled, 0 otherwise
 */
int handle_builtins(char **args)
{
	int i;

	if (strcmp(args[0], "exit") == 0)
		exit(0);

	if (strcmp(args[0], "env") == 0)
	{
		for (i = 0; environ[i]; i++)
			printf("%s\n", environ[i]);
		return (1);
	}

	return (0);
}

/**
 * resolve_command_path - Resolves command path
 * @args: Argument vector
 * Return: Resolved command path or NULL if not found
 */
char *resolve_command_path(char **args)
{
	char *cmd_path = NULL;

	if (strchr(args[0], '/'))
	{
		if (access(args[0], X_OK) == 0)
			cmd_path = strdup(args[0]);
		else
			return (NULL);
	}
	else
	{
		cmd_path = find_command(args[0]);
	}

	return (cmd_path);
}

/**
 * run_command - Forks and executes a command
 * @cmd_path: Full path to command
 * @args: Argument vector
 * Return: Command exit status or 0
 */
int run_command(char *cmd_path, char **args)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == 0)
	{
		execve(cmd_path, args, environ);
		fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
		free(cmd_path);
		exit(127);
	}
	else if (pid < 0)
	{
		perror("fork");
	}
	else
	{
		if (waitpid(pid, &status, 0) != -1)
		{
			if (WIFEXITED(status))
				return (WEXITSTATUS(status));
		}
	}

	return (0);
}

/**
 * execute_cmd - Executes a command with path resolution
 * @args: Argument vector (command and its arguments)
 * Return: 127 if command not found, or exit status
 */
int execute_cmd(char **args)
{
	char *cmd_path;
	int exit_status = 0;

	if (args[0] == NULL)
		return (0);

	if (handle_builtins(args))
		return (0);

	cmd_path = resolve_command_path(args);
	if (cmd_path == NULL)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
		return (127);
	}

	exit_status = run_command(cmd_path, args);

	if (cmd_path != NULL)
	{
		free(cmd_path);
		cmd_path = NULL;
	}

	return (exit_status);
}
