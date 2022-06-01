
#include <stdlib.h>

#include <assert.h>

#include <debug.h>

#include "free.h"

void free_cmdln(struct cmdln* flags)
{
	ENTER;
	
	free(flags);
	
	EXIT;
}

