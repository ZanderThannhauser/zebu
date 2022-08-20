set -ev
gcc -g -Wall -Werror lisp.c -lreadline -o /tmp/lisp && valgrind /tmp/lisp
