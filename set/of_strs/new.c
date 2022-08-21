
#include <debug.h>

#include "struct.h"
#include "new.h"

struct strset* new_strset()
{
	ENTER;
	
	TODO;
	#if 0
	struct strset* this = smalloc(sizeof(*this));
	
	this->data = NULL;
	this->cap = 0;
	this->n = 0;
	
	EXIT;
	return this;
	#endif
}

