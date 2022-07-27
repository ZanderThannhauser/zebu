
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_named_name(void* x)
{
	struct named_name* this = x;
	free(this->name);
	free(this);
}

