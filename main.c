#include "main.h"


int main(int argc, char *argv[] __attribute__((unused)));


/**
 * nonIShell - non interactive shell
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: nothing
 */
void nonIShell(int argc, char *argv[] __attribute__((unused)))
{
	int i;

	for (i = 1; i < argc; i++)
	{
		processIS(argv[i]);
	}
}
/**
 * main - main entry
 * @argc: argument count
 * @argv: argument variable
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	int i;

	i = 0;
	betty();
	if (argc <= 1)
		shell();
	else
		processIS(argv[i]);

	return (0);
}
