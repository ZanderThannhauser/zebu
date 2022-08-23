
#include <stdlib.h>

#include <debug.h>

#include <set/of_regexes/free.h>

#include <arena/dealloc.h>

#include "struct.h"
#include "free.h"

void free_regex_mapping(void* a)
{
	struct regex_mapping* this = a;
	ENTER;
	
	free_regexset(this->original_states);
	
	#ifdef WITH_ARENAS
	arena_dealloc(this->arena, this);
	#else
	free(this);
	#endif
	
	EXIT;
}


