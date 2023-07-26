#ifndef _SHELL_
#define _SHELL_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>

int betty(void);
char* readLine();
char** splitLine(char* line, char* loneCopy);
void exec();

#endif
