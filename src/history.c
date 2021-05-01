#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "history.h"
#include "common.h"

History* initHistory(int maxSize)
{
	History* history = malloc(sizeof(History));
	history->length = 0;
	history->maxSize = maxSize;
	int i = 0;
	char** his = (char**) malloc(maxSize * sizeof(char*));
	history->historyList = his;
	for (i = 0; i < history->maxSize; i++)
	{
		history->historyList[i] = NULL;
	}
	return history;
}


void addHistoryItem(History* history, char* item)
{
	char* str = (char*) malloc(strlen(item) + 8);
	if (history->length > 0)
	{
		if (strcmp(history->historyList[history->length - 1], item) == 0 || strcmp("", item) == 0 || item[0] == '!')
		{
			return;
		}
	}
	strcpy(str, item);

	if (history->length < history->maxSize)
	{
		history->historyList[history->length] = str;
	} else
	{
		int i = 0;
		history->length -= HISTORY_OFFSET;
		for (i = 0; i < history->maxSize - HISTORY_OFFSET; i++) //5 is offset
		{
			if (i < HISTORY_OFFSET)
			{
				free(history->historyList[i]);
			}
			history->historyList[i] = history->historyList[i + HISTORY_OFFSET];
		}
		history->historyList[history->length] = str;
	}
	history->length++;
}

void destroyHistory(History* history)
{
	int i = 0;
	for (i = 0; i < history->length; i++)
	{
		free(history->historyList[i]);
		history->historyList[i] = NULL;
	}
	free(history->historyList);
	history->historyList = NULL;
	history->maxSize = 0;
	history->length = 0;
	free(history);
}

void printHistory(History* history)
{
	int i = 0;
	for (i = 0; i < history->length; i++)
	{
		printf("%d: %s\n", i, history->historyList[i]);
	}
}

void processHistory(char* inputStr, History* hist)
{
	if (inputStr[0] == '!')
	{
		if (inputStr[1] == '!')
		{
			if (hist->length > 0)
			{
				strcpy(inputStr, hist->historyList[hist->length - 1]);
				return;
			}
			else
			{
				strcpy(inputStr, "");
				return;
			}
		}
		strcpy(inputStr, inputStr + 1);
		int num = atoi(inputStr);
		if (hist->length > num)
		{
			strcpy(inputStr, hist->historyList[num]);
			return;
		}
		else
		{
			strcpy(inputStr, "");
			return;
		}
	}
}
