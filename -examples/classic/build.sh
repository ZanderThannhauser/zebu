set -ev
gcc -g -Wall -Werror ./classic.c -o /tmp/classic -lreadline && valgrind /tmp/classic
