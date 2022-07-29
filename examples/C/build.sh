set -ev
gcc -g -Wall -Werror output.c main.c -lreadline -o /tmp/C && valgrind /tmp/C
