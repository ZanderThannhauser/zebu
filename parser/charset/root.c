
#include <debug.h>

#include "complement.h"
#include "root.h"

struct charset* read_root_charset(
	struct memory_arena* arena,
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	struct charset* retval = read_complement_charset(arena, tokenizer, scope);
	
	EXIT;
	return retval;
}

