
#include <debug.h>

#include "struct.h"
#include "new.h"

struct yacc_state* new_yacc_state()
{
	ENTER;
	
	struct yacc_state* this = smalloc(sizeof(*this));
	
	EXIT;
	return this;
}

