
#include <stdlib.h>

#include <debug.h>

#include <arena/dealloc.h>

#include <set/of_tokens/free.h>

#include "struct.h"
#include "free.h"

void free_yacc_stateinfo_node(void* ptr)
{
	struct yacc_stateinfo_node* this = ptr;
	ENTER;
	
	free_tokenset(this->lookaheads);
	
	arena_dealloc(this->arena, this);
	
	EXIT;
}

