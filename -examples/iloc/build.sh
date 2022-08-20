set -ev
gcc -g -Wall -Werror iloc.c -o /tmp/iloc && valgrind /tmp/iloc ./dynamic.il
