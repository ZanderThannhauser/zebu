
#include <stdlib.h>
#include <stdio.h>

#include <debug.h>

#include <defines/argv0.h>

#include "usage.h"

void usage(int code)
{
	printf("usage: %s <args>\n", argv0);
	exit(code);
}


