
#include <stdlib.h>
#include <string.h>

#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct lex_state* new_lex_state()
{
	ENTER;
	
	struct lex_state* this = smalloc(sizeof(*this));
	
	memset(this->transitions, 0, sizeof(this->transitions));
	
	this->EOF_transition_to = NULL;
	
	this->accepts = NULL;
	
	this->kind = 0;
	
	EXIT;
	return this;
}
