set -ev
gcc -g -Wall -Werror math.c -lreadline -o /tmp/math && valgrind /tmp/math
