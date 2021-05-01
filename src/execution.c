#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "common.h"
#include "execution.h"


void execWithArgs(char** argv)
{
	//forking a child
	pid_t pid = fork();

	if (pid == -1)
	{
		//error forking child
		printf("Failed forking child!\n");
		return;
	} else if (pid == 0)
	{
		//child process
		if (execvp(argv[0], argv) < 0)
		{
			printf("Could not execute command!\n");
			exit(0);
		}
	} else
	{
		//parrent process
		wait(NULL);
		return;
	}
}

void execWithArgsPiped(char** argvPipe1, char** argvPipe2)
{
	int pipefd[2];
	pid_t p1, p2; //2 child process

	if (pipe(pipefd) < 0)
	{
		printf("Pipe could not be initialized!");
		return;
	}
	p1 = fork();
	if (p1 < 0)
	{
		printf("Could not fork chill process!");
		return;
	}

	if (p1 == 0)
	{
		//child 1 executing..
		//it only needs to write at the write end
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);

		if (execvp(argvPipe1[0], argvPipe1) < 0)
		{
			printf("Could not execute command 1 in pipe!\n");
			exit(0);
		}

	} else
	{
		//parent executing
		p2 = fork();

		if (p2 < 0) {
			printf("Could not fork!\n");
			return;
		}

		//child 2 executing..
		//it only needs to read at the read end
		if (p2 == 0)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			printf("\n");
			if (execvp(argvPipe2[0], argvPipe2) < 0)
			{
				printf("Could not execute command 2 in pipe!\n");
				exit(0);
			}
		} else
		{
			// parent executing, waiting for two children
			close(pipefd[0]);
			close(pipefd[1]);
			wait(NULL);
			wait(NULL);
		}
	}
}

void execWithArgsAndRedirecting(char** argv, char* fileName, int stream)
{
	//forking a child
	pid_t pid = fork();

	if (pid == -1)
	{
		//error
		printf("Failed forking child..\n");
		return;
	}
	else if (pid == 0)
	{
		FILE* f = NULL;
		if (stream == REDIRECTING_OUTPUT_EXEC)
		{
			f = fopen(fileName, "w");
			dup2(fileno(f), STDOUT_FILENO);
		} else if (stream == REDIRECTING_INPUT_EXEC)
		{
			f = fopen(fileName, "r");
			dup2(fileno(f), STDIN_FILENO);
		}
		close(f);
		//child
		if (execvp(argv[0], argv) < 0)
		{
			printf("Could not execute command..\n");
		}
		exit(0);
	} else
	{
		//parrent
		wait(NULL);
	}
}