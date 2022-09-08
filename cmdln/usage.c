
#include <stdlib.h>
#include <stdio.h>

#include <debug.h>

#include "usage.h"

void usage(int code)
{
	printf("usage: zebu -i <path/to/input.zb> -o <path/to/output/base>\n");
	
	exit(code);
}


