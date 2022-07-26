
#if 0
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct lex_state_cache* new_lex_state_cache(
	struct lex_state* a,
	struct lex_state* b)
{
	struct lex_state_cache* this = smalloc(sizeof(*this));
	
	this->a = a;
	this->b = b;
	
	this->are_equal = true;
	
	return this;
}

#endif
