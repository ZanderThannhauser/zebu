
#include <debug.h>

#include "struct.h"
#include "new.h"

struct named_charset* new_named_charset(
	char* name,
	struct charset* charset)
{
	ENTER;
	
	struct named_charset* this = smalloc(sizeof(*this));
	
	this->name = name;
	this->charset = charset;
	
	EXIT;
	return this;
}

