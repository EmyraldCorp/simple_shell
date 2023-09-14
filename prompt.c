#include "shell.h"
#include <sys/wait.h>

/**
 * display_prompt - ..
 * **av: ...
 * **env:...
 *
 */

void display_prompt(char **av, char **env) {
    char *user_input = NULL;
    size_t input_size = 0;
    ssize_t input_length;
    char *command_argv[] = {NULL, NULL};
    int status;
    pid_t child_pid;

    while (1) {
        printf("our_custom_shell$ ");

        input_length = getline(&user_input, &input_size, stdin);
        if (input_length == -1) {
            free(user_input);
            exit(EXIT_FAILURE);
        }

	if (user_input[input_length - 1] == '\n') {
            user_input[input_length - 1] = '\0';
        }

        command_argv[0] = user_input;

        child_pid = fork();
        if (child_pid == -1) {
            free(user_input);
            exit(EXIT_FAILURE);
        }
        if (child_pid == 0) {
            if (execve(command_argv[0], command_argv, env) == -1) {
                printf("%s: Command not found\n", av[0]);
            }
            exit(EXIT_FAILURE);
        } else {
            wait(&status);
        }
    }
	free(user_input);
}
