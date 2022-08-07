set -ev
gcc -g -Wall -Werror output.c main.c -o /tmp/maia && valgrind /tmp/maia
