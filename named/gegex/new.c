
#include <debug.h>

#include "struct.h"
#include "new.h"

struct named_gegex* new_named_gegex(char* name, struct gegex* gegex)
{
	ENTER;
	
	struct named_gegex* this = smalloc(sizeof(*this));
	
	this->name = name;
	this->gegex = gegex;
	
	EXIT;
	return this;
}

