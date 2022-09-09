
#include <debug.h>

#include <memory/smalloc.h>

#include <string/inc.h>

#include "struct.h"
#include "new.h"

struct named_charset* new_named_charset(
	struct string* name,
	charset_t charset)
{
	ENTER;
	
	struct named_charset* this = smalloc(sizeof(*this));
	
	this->name = inc_string(name);
	this->charset = charset;
	
	EXIT;
	return this;
}

