
#include <stdlib.h>

#include <debug.h>

#include <set/gegex/free.h>

#include "struct.h"
#include "free.h"

void free_gegex_same_as_node(void* ptr)
{
	struct gegex_same_as_node* this = ptr;
	ENTER;
	
	free_gegexset(this->set);
	
	free(this);
	
	EXIT;
}
