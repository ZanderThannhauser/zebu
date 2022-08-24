set -ev
gcc -g -Wall -Werror xml.c -lreadline -o /tmp/xml && valgrind /tmp/xml
