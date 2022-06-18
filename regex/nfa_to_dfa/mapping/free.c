
#include <debug.h>

#include "struct.h"
#include "free.h"

#include "../stateset/free.h"

void free_mapping(void* a)
{
	struct mapping* this = a;
	ENTER;
	
	free_stateset(this->original_states);
	
	free(this);
	
	EXIT;
}


