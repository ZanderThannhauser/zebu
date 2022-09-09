
#include <debug.h>

#include <memory/smalloc.h>

#include <string/inc.h>

#include "struct.h"
#include "new.h"

struct named_gegex* new_named_gegex(
	struct string* name,
	struct gegex* gegex)
{
	ENTER;
	
	struct named_gegex* this = smalloc(sizeof(*this));
	
	this->name = inc_string(name);
	this->gegex = gegex;
	
	EXIT;
	return this;
}

