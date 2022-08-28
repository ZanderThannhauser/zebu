
#include <stdlib.h>

#include <debug.h>

#include <set/regex/free.h>

#include "struct.h"
#include "free.h"

void free_regex_same_as_node(void* ptr)
{
	struct regex_same_as_node* this = ptr;
	ENTER;
	
	free_regexset(this->set);
	
	free(this);
	
	EXIT;
}
