#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "common.h"
#include "utils.h"
#include "parsing.h"

void initShell(char* ruser, char *rdir)
{
	clear();
	char *user = getenv("USER");
	printf("simple operating shell\n");
	printf("USER is: %s\n\n", user);
	char dir[MAX_LIMIT];
	getcwd(dir, sizeof(dir));

	strcpy(rdir, dir);
	strcpy(ruser, user);
}

int getInput(char* str)
{
	/*fgets(str, MAX_LIMIT, stdin);
	str[strlen(str) - 1] = '\0';*/
	char* buf; 
    buf = readline("$ "); 
    if (strlen(buf) != 0) { 
        add_history(buf); 
        strcpy(str, buf); 
        return 0; 
    } else 
    { 
        return 1; 
    } 
}

void processUserCMD(char** cmd, char* dir, char* preDir, char* user)
{
	if(strcmp(cmd[0], "cd") == 0)
	{
		if(strcmp(cmd[1], "~") == 0)
		{
			char userdir[MAX_LIMIT] = "/home/";
			strcat(userdir, user);
			chdir(userdir);
			return;
		}
		if(strcmp(cmd[1], "-") == 0)
		{
			chdir(preDir);
			strcpy(preDir, dir);
			return;
		}
		chdir(cmd[1]);
	}

	if(strcmp(cmd[0], "exit") == 0)
	{
		exit(0);
	}
}

int processInput(char* inputStr, char** tokens)
{
	char inputCopy[MAX_LIMIT];
	strcpy(inputCopy, inputStr);

	int i = strlen(inputCopy) - 1;;
	while(inputCopy[i] == 32 && i>=0)
	{
		inputCopy[i] = '\0';
		i--;
	}

	if(strlen(inputCopy) == 0) return;

	parseSpace(inputCopy, tokens);
	char* listUserCMD[] = {"cd", "exit"};
	i = 0;
	int switchOwnArg = 0;
	for (i = 0; i < 2; i++) {
		if (strcmp(tokens[0], listUserCMD[i]) == 0)
		{
			switchOwnArg = i + 1;
			break;
		}
	}

	switch (switchOwnArg) {
	case 1:
	case 2:
		return USER_EXEC;
	default:
		break;
	}

	int piped = 0;
	int redirect = 0;

	redirect = parseRedirecting(inputStr, tokens);
	if (redirect == 0)
	{
		piped = parsePipe(inputStr, tokens);
	}

	if (redirect)
	{
		if (redirect == REDIRECTING_INPUT_EXEC)
			return REDIRECTING_INPUT_EXEC;
		else
			return REDIRECTING_OUTPUT_EXEC;
	}

	if (piped == SIMPLE_EXEC)
	{
		return SIMPLE_EXEC;
	}
	else
	{
		return PIPE_EXEC;
	}
}
