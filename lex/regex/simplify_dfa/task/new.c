
#include <debug.h>

/*#include <memory/smalloc.h>*/

#include "struct.h"
#include "new.h"

struct simplify_task* new_simplify_task(
	struct regex* a, struct regex* b,
	unsigned hopcount)
{
	ENTER;
	
	TODO;
	#if 0
	struct simplify_task* this = smalloc(sizeof(*this));
	
	this->pair.a = a;
	this->pair.b = b;
	
	this->hopcount = hopcount;
	
	EXIT;
	return this;
	#endif
}

