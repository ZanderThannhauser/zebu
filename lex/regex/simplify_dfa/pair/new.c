
#include <assert.h>

#include <debug.h>

/*#include <memory/smalloc.h>*/

#include "struct.h"
#include "new.h"

struct pair* new_pair(struct regex* a, struct regex* b)
{
	TODO;
	#if 0
	struct pair* this = smalloc(sizeof(*this));
	
	assert(a < b);
	
	this->a = a;
	this->b = b;
	
	return this;
	#endif
}

