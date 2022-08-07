set -ev
gcc -g -Wall -Werror json.c -lreadline -o /tmp/math && valgrind /tmp/math
