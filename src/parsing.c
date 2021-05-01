#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "parsing.h"
#include "common.h"

void parseSpace(char* str, char** parsedSpace)
{
	int i = 0;

	for (i = 0; i < MAXLIST; i++)
	{
		parsedSpace[i] = strsep(&str, " ");

		if (parsedSpace[i] == NULL)
		{
			break;
		}
		if (strlen(parsedSpace[i]) == 0)
		{
			i--;
		}
	}
}

int parsePipe(char* str, char** parsedPipe)
{
	int i = 0;
	for (i = 0; i < 2; i++)
	{
		parsedPipe[i] = strsep(&str, "|");
		if (parsedPipe[i] == NULL)
		{
			break;
		}
	}

	if (parsedPipe[1] == NULL)
	{
		return SIMPLE_EXEC; //no '|' is found.
	}
	else
	{
		return PIPE_EXEC;
	}
}

int parseRedirecting(char* str, char** parseRedirecting)
{
	int i = 0;
	int caseRet = 0; //not found redirect
	for (i = 0; i < 2; i++)
	{
		parseRedirecting[i] = strsep(&str, ">");
		caseRet = REDIRECTING_OUTPUT_EXEC;
		if (parseRedirecting[i] == NULL)
		{
			parseRedirecting[i] = strsep(&str, "<");
			caseRet = REDIRECTING_INPUT_EXEC;
			if (parseRedirecting[i] == NULL)
			{
				caseRet = 0;
				break;
			}
		}
	}

	if (caseRet == REDIRECTING_OUTPUT_EXEC)
	{
		return REDIRECTING_OUTPUT_EXEC;
	}
	else if (caseRet == REDIRECTING_INPUT_EXEC)
	{
		return REDIRECTING_INPUT_EXEC;
	}

	return 0;
}