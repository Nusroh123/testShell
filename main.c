#include "main.h"

/**
 * main - main entry
 * Return: 0 on success
 */
int  main(int argc __attribute__((unused)), char* argv[])
{
	char* line = NULL;
	char* lineCopy = NULL;

	while ((isatty(STDIN_FILENO) != 0))
	{
		write(STDOUT_FILENO, "$ ", 2);
		line = readLine();
		splitLine(line, lineCopy);
		exec(argv);
	}

	free(line);
	line = NULL;
	return (0);
	
}
