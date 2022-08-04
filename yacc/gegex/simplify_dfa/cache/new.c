
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct gegex_cache* new_gegex_cache(const struct gegex* a, const struct gegex* b)
{
	struct gegex_cache* this = smalloc(sizeof(*this));
	
	this->a = a;
	this->b = b;
	
	this->are_equal = true;
	
	return this;
}

