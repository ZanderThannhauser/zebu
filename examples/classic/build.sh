set -ev
gcc -g -Wall -Werror output.c main.c -o /tmp/classic && valgrind /tmp/classic
