
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "new.h"

struct charset* new_charset_from_range(
	char low, char high)
{
	ENTER;
	
	dpvc(low);
	dpvc(high);
	
	TODO;
	#if 0
	struct charset* this = smalloc(sizeof(*this));
	
	assert(high >= low);
	
	this->len = (high - low) + 1;
	
	dpv(this->len);
	
	char* chars = this->chars = smalloc(this->len);
	
	while (low <= high) *chars++ = low++;
	
	this->is_complement = false;
	
	this->refcount = 1;
	
	EXIT;
	return this;
	#endif
}














