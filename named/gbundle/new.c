
#include <debug.h>

/*#include <memory/smalloc.h>*/

#include "struct.h"
#include "new.h"

struct named_gbundle* new_named_gbundle(
	char* name,
	struct gegex* start,
	struct gegex* end)
{
	ENTER;
	
	TODO;
	#if 0
	struct named_gbundle* this = smalloc(sizeof(*this));
	
	this->name = name;
	this->start = start;
	this->end = end;
	
	dpvs(this->name);
	
	EXIT;
	return this;
	#endif
}

