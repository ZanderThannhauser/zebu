
#include <stdlib.h>
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct gegex_simplify_task* new_gegex_simplify_task(
	struct gegex* a, struct gegex* b,
	unsigned hopcount)
{
	ENTER;
	
	struct gegex_simplify_task* this = smalloc(sizeof(*this));
	
	this->pair.a = a;
	this->pair.b = b;
	
	this->hopcount = hopcount;
	
	EXIT;
	return this;
}
