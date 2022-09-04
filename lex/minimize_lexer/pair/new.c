
#include <stdlib.h>

#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "new.h"

struct lex_pair* new_lex_pair(
	struct lex_state* a, struct lex_state* b)
{
	ENTER;
	
	struct lex_pair* this = smalloc(sizeof(*this));
	
	assert(a < b);
	
	this->a = a;
	this->b = b;
	
	EXIT;
	return this;
}
