#include "main.h"


/**
 * processIS - process non interctive mode
 * @line: command
 * Return: nothing
 */

void processIS(char *line)
{
	size_t lineLen;
	int count;
	char *token;
	char *argv[100] =  {NULL};

	line = NULL;
	lineLen = 0;
	count = 0;
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
			argv[count] = malloc(_strlen(token) + 1);
			_strcpy(argv[count], token);
			token = strtok(NULL, " \n\t\r");
			count++;
		}
		argv[count] = NULL;

		if (argv[0] == NULL || count == 0)
		{
			continue;
		}

	}
}
