
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "new.h"

struct lex_simplify_task* new_lex_simplify_task(
	struct lex_state* a, struct lex_state* b,
	unsigned hopcount)
{
	ENTER;
	
	struct lex_simplify_task* this = smalloc(sizeof(*this));
	
	this->pair.a = a;
	this->pair.b = b;
	
	this->hopcount = hopcount;
	
	EXIT;
	return this;
}
