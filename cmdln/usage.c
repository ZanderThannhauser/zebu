
#include <stdlib.h>
#include <stdio.h>

#include <debug.h>

#include <defines/argv0.h>

#include "usage.h"

void usage(int code)
{
	printf("usage: %s -i <path/to/input.zb> -o <path/to/output/base>\n", argv0);
	
	exit(code);
}


