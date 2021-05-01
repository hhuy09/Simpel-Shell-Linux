#ifndef _UTILS
#define _UTILS 1

void initShell(char* user, char *dir);
int getInput(char* str);
int processInput(char* inputStr, char** tokens);
void processUserCMD(char** cmd, char* dir, char* preDir, char* user);

#endif