
#ifdef WITHOUT_ARENAS

#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <yacc/gegex/state/free.h>

#include "struct.h"
#include "free.h"

void free_named_grammar(void* ptr)
{
	ENTER;
	
	struct named_grammar* const this = ptr;
	
	free(this->name);
	
	free_gegex(this->grammar);
	
	free(this);
	
	EXIT;
}

#endif
