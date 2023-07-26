#include "main.h"

/**
 * exec - execute the currebt running program from the child instance
 * @args:  program arguments
 * Return: Nothing on success
 */
void exec(void)
{
	int status;
	pid_t childPid;
	char *argv[] = {" ", NULL};
	execve(argv[0], argv, NULL);
	childPid = fork();

	if (childPid == 0)
	{
		if (execve(argv[0], argv, NULL) == -1)
		{
			perror("Not a command");
			exit(EXIT_FAILURE);
		}

	}
	else if (childPid > 0)
	{
		wait(&status);
		if (status != 0)
			exit(2);
	}
	else
	{
		perror("running childPid < 0");
		exit(EXIT_FAILURE);
	}
}
