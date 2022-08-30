
#include <debug.h>

#include <set/unsignedchar/inc.h>

#include "struct.h"
#include "new.h"

struct named_charset* new_named_charset(
	char* name,
	bool is_complement,
	struct unsignedcharset* charset)
{
	ENTER;
	
	struct named_charset* this = smalloc(sizeof(*this));
	
	this->name = name;
	this->is_complement = is_complement;
	this->charset = inc_unsignedcharset(charset);
	
	EXIT;
	return this;
}

