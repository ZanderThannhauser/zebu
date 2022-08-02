
#include <stdlib.h>

#include <debug.h>

#include <set/of_gegexes/free.h>

#include "struct.h"
#include "free.h"

void free_gegex_mapping(void* a)
{
	struct gegex_mapping* this = a;
	ENTER;
	
	free_gegexset(this->original_states);
	
	free(this);
	
	EXIT;
}


