
#include <string.h>
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "clone.h"

struct charset* clone_charset(const struct charset* cloneme)
{
	ENTER;
	
	struct charset* this = malloc(sizeof(*this));
	
	this->chars = memcpy(malloc(cloneme->len), cloneme->chars, cloneme->len);
	
	this->len = cloneme->len;
	
	this->is_complement = cloneme->is_complement;
	
	EXIT;
	return this;
}

