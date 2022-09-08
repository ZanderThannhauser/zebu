set -ev
gcc -g -Wall -Werror output.c -lreadline -o /tmp/C && valgrind /tmp/C
