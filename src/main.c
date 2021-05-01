#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "common.h"
#include "execution.h"
#include "history.h"
#include "parsing.h"
#include "utils.h"

int main()
{
	char userName[MAX_LIMIT] = "";
	char dir[MAX_LIMIT] = "";
	char preDir[MAX_LIMIT] = "";
	char inputStr[MAX_LIMIT] = "";

	char* argv[MAXLIST];
	char* argvPipe[MAXLIST];

	char* tokens[2];
	History *hist = initHistory(MAXLIST);

	initShell(userName, dir);
	while (1)
	{
		getcwd(dir, sizeof(dir));
		printf("%s@linux:~%s", userName, dir);
		strcpy(inputStr, "");
		getInput(inputStr);
		addHistoryItem(hist, inputStr);
		processHistory(inputStr, hist);

		if (strcmp("history", inputStr) == 0)
		{
			printHistory(hist);
			continue;
		}
				
		int caseProcess = processInput(inputStr, tokens);
		
		switch (caseProcess)
		{
		case SIMPLE_EXEC:
			//printf("SIMPLE_EXEC\n");
			parseSpace(inputStr, argv);
			execWithArgs(argv);
			break;

		case PIPE_EXEC:
			//printf("PIPE_EXEC\n");
			parseSpace(tokens[0], argv);
			parseSpace(tokens[1], argvPipe);
			execWithArgsPiped(argv, argvPipe);
			break;

		case REDIRECTING_OUTPUT_EXEC:
			//printf("REDIRECTING_OUTPUT_EXEC\n");
			parseSpace(inputStr, argv);
			execWithArgsAndRedirecting(argv, tokens[1], REDIRECTING_OUTPUT_EXEC);
			break;

		case REDIRECTING_INPUT_EXEC:
			//printf("REDIRECTING_INPUT_EXEC\n");
			parseSpace(inputStr, argv);
			execWithArgsAndRedirecting(argv, tokens[1], REDIRECTING_INPUT_EXEC);
			break;

		case USER_EXEC:
			//printf("USER_EXEC\n");
			processUserCMD(tokens, dir, preDir, userName);
			break;

		default:
			break;
		}
	}
	destroyHistory(hist);
	hist = NULL;
	return 0;
}

