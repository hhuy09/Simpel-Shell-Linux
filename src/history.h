#ifndef _HISTORY
#define _HISTORY 1

typedef struct {
    int length;
    int maxSize;
    char** historyList;
} History;

History* initHistory(int maxSize);
void addHistoryItem(History* history, char* item);
void destroyHistory(History* history);
void printHistory(History* history);

void processHistory(char* inputStr, History* hist);

#endif