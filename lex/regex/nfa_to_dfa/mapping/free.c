
#include <stdlib.h>

#include <debug.h>

#include <set/of_regexes/free.h>

#include "struct.h"
#include "free.h"

void free_regex_mapping(void* a)
{
	struct regex_mapping* this = a;
	ENTER;
	
	free_regexset(this->original_states);
	
	free(this);
	
	EXIT;
}


