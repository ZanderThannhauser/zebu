
#include <debug.h>

#include <memory/smalloc.h>
#include <memory/smemdup.h>

#include "struct.h"
#include "new.h"

struct charset* new_charset_from_range(
	char low, char high)
{
	ENTER;
	
	dpvc(low);
	dpvc(high);
	
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
}














