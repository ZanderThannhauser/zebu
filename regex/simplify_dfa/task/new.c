
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "new.h"

struct regex_simplify_task* new_regex_simplify_task(
	struct regex* a, struct regex* b,
	unsigned hopcount)
{
	ENTER;
	
	struct regex_simplify_task* this = malloc(sizeof(*this));
	
	this->pair.a = a;
	this->pair.b = b;
	
	this->hopcount = hopcount;
	
	EXIT;
	return this;
}
