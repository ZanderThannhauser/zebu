
#include <debug.h>

#include "struct.h"
#include "min.h"

unsigned char unsignedcharset_min(const struct unsignedcharset* this)
{
	ENTER;
	
	assert(this->n);
	
	unsigned char* min = this->tree->head->item;
	
	dpv(*min);
	
	EXIT;
	return *min;
}

