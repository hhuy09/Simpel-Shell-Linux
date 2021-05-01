rm build/history.o
rm build/execution.o
rm build/parsing.o
rm build/utils.o
rm build/main.o

rmdir build

rm bin/osh

rmdir bin

mkdir bin
mkdir build

gcc src/history.c -w -o build/history.o -c
gcc src/execution.c -w -o build/execution.o -c
gcc src/parsing.c -w -o build/parsing.o -c
gcc src/utils.c -w -o build/utils.o -c
gcc -Wall -c -w -g src/main.c -o build/main.o 

#gcc src/main.c -o build/main.o -c

gcc build/history.o build/execution.o build/parsing.o build/utils.o build/main.o -lreadline -o bin/osh 