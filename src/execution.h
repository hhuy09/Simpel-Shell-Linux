#ifndef _EXECUTION
#define _EXECUTION 1

void execWithArgs(char** argv);
void execWithArgsAndRedirecting(char** argv, char* fileName, int stream);
void execWithArgsPiped(char** argvPipe1, char** argvPipe2);

#endif