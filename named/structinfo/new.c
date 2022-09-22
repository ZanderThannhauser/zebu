
#include <debug.h>

#include <memory/smalloc.h>

#include <string/inc.h>

#include <yacc/structinfo/inc.h>

#include "struct.h"
#include "new.h"

struct named_structinfo* new_named_structinfo(
	struct string* name,
	struct structinfo* structinfo)
{
	ENTER;
	
	struct named_structinfo* this = smalloc(sizeof(*this));
	
	this->name = inc_string(name);
	
	this->structinfo = inc_structinfo(structinfo);
	
	EXIT;
	return this;
}

