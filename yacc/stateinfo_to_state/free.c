
#include <debug.h>

#include "../stateinfo/free.h"

#include "struct.h"
#include "free.h"

void free_stateinfo_to_state(void* ptr)
{
	struct stateinfo_to_state* this = ptr;
	ENTER;
	
	free_yacc_stateinfo(this->stateinfo);
	
	free(this);
	
	EXIT;
}

