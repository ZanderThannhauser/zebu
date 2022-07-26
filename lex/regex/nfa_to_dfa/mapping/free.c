
#include <debug.h>

#include <set/of_regexes/free.h>

#include "struct.h"
#include "free.h"

void free_mapping(void* a)
{
	struct mapping* this = a;
	ENTER;
	
	free_regexset(this->original_states);
	
	free(this);
	
	EXIT;
}


