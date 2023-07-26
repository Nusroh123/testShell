#include "main.h"

/**
 * readLine - read what is input on the terminal by the user
 * Return: what was read
 */
char *readLine(void)
{
	char *line;
	char *lineCopy;
	size_t lineLen;
	ssize_t read;

	line = NULL;
	lineCopy = NULL;
	lineLen = 0;

	read = getline(&line, &lineLen, stdin);
	/**printf("%s/n", line);**/

	if (read == -1)
	{
		perror("Exiting...");
		exit(EXIT_FAILURE);
	}

	lineCopy = (char *)malloc(sizeof(char) * read + 1);
	if (lineCopy == NULL)
	{
		perror("Memory allocation error");
	}
	strcpy(lineCopy, line);
	free(line);
	free(lineCopy);
	return (line);
}
