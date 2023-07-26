#include "main.h"

/**
 * shell - separate input and execute
 * Return: 0 on success
 */
int shell(void)
{
	char *line;
	size_t lineLen;
	int count, i;
	char *token;
	char *argv[100] =  {NULL};
	struct stat *sFile;
	pid_t childPid;

	line = NULL;
	lineLen = 0;
	count = 0;
	sFile = malloc(sizeof(struct stat));

	while (isatty(STDIN_FILENO) != 0)
	{
		write(STDOUT_FILENO, "#cisfun: ", 10);
		if (getline(&line, &lineLen, stdin) == -1)
		{
			perror("Exiting..");
			exit(EXIT_FAILURE);
		}

		token = strtok(line, " \n\t\r");
		while (token != NULL && count < 99)
		{
			argv[count] = strdup(token);
			token = strtok(NULL, " \n\t\r");
			count++;
		}
		argv[count] = NULL;

		if (argv[0] == NULL || count == 0)
		{
			continue;
		}

		if (stat(argv[0], sFile) == 0)
		{
			childPid = fork();
			if (childPid == 0)
			{
				if (execve(argv[0], argv, NULL) == -1)
				{
					perror("");
					exit(EXIT_FAILURE);
				}
			}
			else if (childPid == -1)
			{
				perror("Fork error");
				continue;
			}
			else
			{
				wait(NULL);
			}

			for (i = 0; i < count; i++)
			{
				free(argv[i]);
			}

		}
		else
		{
			perror("Error");
			continue;
		}
	}
	free(line);
	free(sFile);
	return (0);
}
