
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct regex_cache* new_regex_cache(const struct regex* a, const struct regex* b)
{
	struct regex_cache* this = smalloc(sizeof(*this));
	
	this->a = a;
	this->b = b;
	
	this->are_equal = true;
	
	return this;
}

