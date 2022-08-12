
#include <debug.h>

#include <set/of_tokens/free.h>

#include "struct.h"
#include "free.h"

void free_yacc_stateinfo_node(void* ptr)
{
	struct yacc_stateinfo_node* this = ptr;
	ENTER;
	
	free_tokenset(this->lookaheads);
	
	free(this);
	
	EXIT;
}

