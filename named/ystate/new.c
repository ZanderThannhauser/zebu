
#include <debug.h>

/*#include <memory/smalloc.h>*/

#include "struct.h"
#include "new.h"

struct named_ystate* new_named_ystate(
	char* name,
	struct yacc_state* ystate)
{
	ENTER;
	
	TODO;
	#if 0
	struct named_ystate* this = smalloc(sizeof(*this));
	
	this->name = name;
	this->ystate = ystate;
	
	dpvs(this->name);
	
	dpv(this);
	
	EXIT;
	return this;
	#endif
}

