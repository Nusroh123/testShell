#include "main.h"

/**
 * splitLine - separate input 
 * @line: input
 * Return: splitted input
 */
char** splitLine(char* line, char* lineCopy)
{
	int count, i;
	char* token;
	char* argv[100];
	char** av;
	count = 0;
	token = strtok(line, " /t/n/r");
	while (token != NULL && count < 63)
	{
		token = strtok(NULL, " /r/t/n");
		count++;
	}

	if (argv[0] == NULL)
	{
		perror("Memory allocation Error");
		exit(EXIT_FAILURE);
	}
	
	lineCopy = strdup(line);
	token = strtok(lineCopy, " /t/n/r");
	for (i = 0; i < count; i++ )
	{
		argv[i] = strdup(token);
		token = strtok(NULL, " /t/n/r");
	}
	av = argv;
	argv[count] = NULL;
	free(lineCopy);
	return (av);
}
