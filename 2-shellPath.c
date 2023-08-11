#include "main.h"

char *location (char *path, char *arg)
{
	char *pathCopy, *pathToken, *filePath;
	char *delim = ":";

	pathCopy = strdup(path);
	pathToken = strtok(pathCopy, delim);
	filePath = malloc(strlen(arg) + strlen(pathToken) + 2);
	while (pathToken != NULL)
	{
		strcpy(filePath, pathToken);
		strcat(filePath, "/");
		strcat(filePath, arg);
		strcat(filePath, "\0");

		if (filePath)
			pathToken = strtok(NULL, delim);
	}

	free(filePath);
	return (NULL);

}

char *takeLocation(char *arg)
{
	char *path;

	path = getenv("PATH");
	
	if (path)
	{
		path = location(path, arg);
		return (path);
	}

	return (NULL);
}
