#ifndef _COMMON
#define _COMMON 1

#define SIMPLE_EXEC 1111
#define PIPE_EXEC 2222
#define REDIRECTING_INPUT_EXEC 3333
#define REDIRECTING_OUTPUT_EXEC 4444
#define USER_EXEC 5555

#define HISTORY_OFFSET 5

#define MAX_LIMIT 1024 //max number of letters
#define MAXLIST 100 //max number of commands

#define clear() printf("\033[H\033[J") //clear screen

#endif