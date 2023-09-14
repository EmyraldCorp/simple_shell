#include "shell.h"

int main(int ac, char **av, char **env)
{
	if (ac == 1)
		display_prompt(av, env);
	return (0);
}
