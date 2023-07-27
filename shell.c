#include "main.h"

int shell(void);
int _strlen(char *s);
/**
 * _strcpy - it copiess a string
 * @dest: destination string
 * @src: source string
 * Return: a character
 */
char *_strcpy(char *dest, const char *src)
{
	char *d;
	int i;

	d = dest;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}

	dest[i] = '\0';
	return (d);
}


/**
 * _strlen - Function that rturns the length of a string
 * @s: Length of the string
 * Return: The value of s
 */
int _strlen(char *s)
{
	int l = 0;

	while (*s++)
		l++;
	return (l);
}

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
