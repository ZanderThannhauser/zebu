
#include <stdlib.h>

#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "new.h"

struct regex_pair* new_regex_pair(
	struct regex* a, struct regex* b)
{
	ENTER;
	
	struct regex_pair* this = malloc(sizeof(*this));
	
	assert(a < b);
	
	this->a = a;
	this->b = b;
	
	EXIT;
	return this;
}
