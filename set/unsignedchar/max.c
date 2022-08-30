
#include <debug.h>

#include "struct.h"
#include "max.h"

unsigned char unsignedcharset_max(const struct unsignedcharset* this)
{
	ENTER;
	
	assert(this->n);
	
	unsigned char* max = this->tree->tail->item;
	
	dpv(*max);
	
	EXIT;
	return *max;
}

