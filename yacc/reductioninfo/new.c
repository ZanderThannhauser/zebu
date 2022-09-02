
#include <debug.h>

#include "struct.h"
#include "inc.h"
#include "new.h"

struct reductioninfo* new_reductioninfo(
	struct string* tag,
	unsigned index,
	struct reductioninfo* prev)
{
	ENTER;
	
	struct reductioninfo* this = smalloc(sizeof(*this));
	
	this->tag = inc_string(tag);
	
	this->index = index;
	
	this->prev = inc_reductioninfo(prev);
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

