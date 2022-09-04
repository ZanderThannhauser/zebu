
#include <stdlib.h>

#include <debug.h>

#include <set/lexstate/free.h>

#include "struct.h"
#include "free.h"

void free_lex_same_as_node(void* ptr)
{
	struct lex_same_as_node* this = ptr;
	ENTER;
	
	free_lexstateset(this->set);
	
	free(this);
	
	EXIT;
}
