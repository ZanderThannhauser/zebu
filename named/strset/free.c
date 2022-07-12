
#include <debug.h>

#include <strset/free.h>

#include "struct.h"
#include "free.h"

void free_named_strset(void* a)
{
	struct named_strset* this = a;
	free_strset(this->strset);
	free(this);
}

