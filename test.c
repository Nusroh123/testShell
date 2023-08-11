#include "main.h"

int main(int ac, char *av[], char **env)
{
        char *buffer;
        size_t charNum;
        char *tok[64];
        int i, j, status;
        pid_t childPid;

        i = 0;
        j = 0;
        buffer = NULL;
        charNum = 0;
        tok[64] = "/bin/ls, -l, ls, NULL";

        while (isatty(STDIN_FILENO) != 0)
        {
                write(STDOUT_FILENO, "> ", 3);
                while (getline(&buffer, &charNum, stdin) != -1)
                {
                        /**free(buffer);
                          perror("Exiting shell");
                          exit(EXIT_FAILURE);
                         **/
                        /**else if (getline(&buffer, &charNum, stdin) != -1)
                          continue;
                         **/
                        while (buffer[j])
                        {
                                if (buffer[j] == '\n')
                                        buffer[j] = 0;
                                j++;
                        }

                        tok[0] = strtok(buffer, " \n");
                        while (tok[i])/**i.e tok[i] != '\0'**/
                        {
                                tok[++i] = strtok(NULL, " \n");
                        }
                        tok[i] = NULL;

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
                                wait(&status);
                }
        }

        free(buffer);
        return (0);
}
