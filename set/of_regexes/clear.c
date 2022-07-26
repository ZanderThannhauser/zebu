
#include <debug.h>

#include "struct.h"
#include "clear.h"

void regexset_clear(struct regexset* this)
{
	ENTER;
	this->n = 0;
	EXIT;
}

