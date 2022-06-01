
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

int new_lex(struct lex** new, bool verbose)
{
	int error = 0;
	ENTER;
	
	struct lex* this;
	
	error = smalloc((void**) &this, sizeof(*this));
	
	if (!error)
	{
		this->verbose = verbose;
		
		*new = this;
	}
	
	EXIT;
	return error;
}

