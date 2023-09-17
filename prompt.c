#include "shell.h"
#include <sys/wait.h>
#define MAX_COMMAND 10

/**
 * display_prompt - ..
 * av: argument vector
 * env:environment vector
 *
 */

void display_prompt(char **av, char **env)
{
	char *user_input = NULL;
	size_t input_size = 0;
	ssize_t input_length;
	char *command_argv[MAX_COMMAND];
	int d, status;
	pid_t child_pid;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("our_custom_shell$ ");

		input_length = getline(&user_input, &input_size, stdin);
		if (input_length == -1)
		{
			free(user_input);
			exit(EXIT_FAILURE);
		}
		if (user_input[input_length - 1] == '\n')
			user_input[input_length - 1] = '\0';
		d = 0;
		command_argv[d] = strtok(user_input, " ");
		while (command_argv[d])
		{
			command_argv[++d] = strtok(NULL, " ");
		}
		child_pid = fork();
		if (child_pid == -1)
		{
			free(user_input);
			exit(EXIT_FAILURE);
		}
		if (child_pid == 0)
		{
			if (execve(command_argv[0], command_argv, env) == -1)
				printf("%s: No such file or directory\n", av[0]);
		}
		else
			wait(&status);
	}
}
