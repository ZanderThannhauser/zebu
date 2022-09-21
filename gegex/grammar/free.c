
#include <stdlib.h>

#include <debug.h>

#include <string/free.h>

#include <yacc/structinfo/free.h>

#include "struct.h"
#include "free.h"

void free_gegex_grammar_transition(
	struct gegex_grammar_transition* this)
{
	ENTER;
	
	free_structinfo(this->structinfo);
	
	free_string(this->grammar);
	
	free(this);
	
	EXIT;
}

