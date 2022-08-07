set -ev
gcc -g -Wall -Werror maia.c -o /tmp/maia && valgrind /tmp/maia ./input.txt -o ./out.dot
