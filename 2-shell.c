#include "main.h"

int main(int ac, char *tok[], char **env)
{
	char *buffer;
	size_t charNum;
	/**char *tok[64];**/
	int i, j, status;
	pid_t childPid, waitPid;
	char *path;
	char **envp, *pathCopy, *pathToken, executablePath;

	i = 0;
	j = 0;
	buffer = NULL;
	charNum = 0;
	/**tok[64] = "/bin/ls, -l, ls, NULL";**/
	path = NULL;
	executablePath = malloc(strlen(tok) + strlen(pathToken) + 2);
	(void)ac;

	/**Finding the PATH environment variable in the environ array
	 * Comparing it with PATH**/
	for(envp = env; *envp != NULL; ++envp)
	{
		if (strncmp(*envp, "PATH=", 5) == 0)
		{
			path = *envp + 5;
			break;
		}
	}
	if (path == NULL)
	{
		perror("Cannot retrieve PATH");
	}

	while (1)
	{
		if (isatty(STDIN_FILENO) != 0)/**check if it is interactive i.e not piped**/
			write(STDOUT_FILENO, "> ", 3);/**Prompt**/

		if (getline(&buffer, &charNum, stdin) == -1)/**Handles EOF, no more input**/
			break;
		while (buffer[j])/**Remove newline character**/
		{
			if (buffer[j] == '\n')
				buffer[j] = 0;
			j++;
		}

		tok[0] = strtok(buffer, " \n");/**Tokenize input**/
		i = 0;
		while (tok[i])/**i.e tok[i] != '\0'**/
		{
			printf("Token %d: %s\n", i, tok[i]);
			i++;
			tok[i] = strtok(NULL, " \n");
		}

		if (i > 0)
		{
			tok[i] = NULL;

			pathCopy = strdup(path);
			pathToken = strtok(pathCopy, ":");
			while (pathToken)
			{
				strcpy(executablePath, pathToken);
				strcat(executablePath, "/");
				strcat(executablePath, tok);
				strcat(executablePath, "\0");
				if (executablePath)
					pathToken = strtok(NULL, delim);
				if (access(executablePath, X_OK) == 0)
				{
					printf("Executable path: %s\n", executablePath);
					childPid = fork();
					if (childPid < 0)
					{
						perror("fork failed");
						free(buffer);
						continue;
					}
					else if (childPid == 0)
					{
						if (execve(tok[0], tok, env) == -1)
						{
							perror("execve failed");
							exit(EXIT_FAILURE);
						}
					}
					else
					{
						waitPid = wait(&status);
						if (waitPid == -1)
							perror("wait failed");
						else
							printf("Child process %d finished with status: %d\n", waitPid, status);

					}
					break;
				}
				pathToken = strtok(NULL, ":");
			}
			free(pathCopy);
		}
		free(executablePath);
	}
	fflush(stdout);
	free(buffer);
	return (0);
}
