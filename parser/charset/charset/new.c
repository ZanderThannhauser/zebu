
#include <debug.h>

#include <memory/smalloc.h>
#include <memory/smemdup.h>

#include "struct.h"
#include "new.h"

struct charset* new_charset(
	const char* src, size_t len,
	bool is_complement)
{
	ENTER;
	
	struct charset* this = smalloc(sizeof(*this));
	
	this->chars = smemdup(src, len);
	this->len = len;
	
	this->is_complement = is_complement;
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

