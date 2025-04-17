#include "shell.h"

/**
 * main - Entry point of the shell
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char **args;
	int status;
	int should_exit = 0;

	while (!should_exit)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 4);

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			free(line);
			exit(0);
		}

		args = parse_line(line);
		if (args[0] != NULL)
		{
			if (strcmp(args[0], "exit") == 0)
			{
				should_exit = 1;
			}
			else
			{

				status = execute_cmd(args);
				if (status == 127)
				{
					free(args);
					free(line);
					exit(127);
				}
			}
		}

		free(args);
	}

	free(line);
	return (0);
}

