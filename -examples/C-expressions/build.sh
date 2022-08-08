set -ev
gcc -g -Wall -Werror C.c -lreadline -o /tmp/C && valgrind /tmp/C
