
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct lex* new_lex(bool verbose)
{
	ENTER;
	
	struct lex* this = smalloc(sizeof(*this));
	
	this->verbose = verbose;
	
	EXIT;
	return this;
}

