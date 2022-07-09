
#include <stdlib.h>
#include <debug.h>

#include "free.h"

void free_lex(struct lex* this)
{
	free(this);
}

