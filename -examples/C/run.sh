set -ev
# gcc -Wall -Werror ./C.c -o /tmp/C && valgrind /tmp/C input.c -o out.dot
gcc -Wall -Werror ./C.c -o /tmp/C -lreadline && valgrind /tmp/C
