
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_regexset(struct regexset* this)
{
	free(this->data);
	free(this);
}

