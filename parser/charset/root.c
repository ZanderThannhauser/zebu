
#include <debug.h>

#include "complement.h"
#include "root.h"

struct charset* read_root_charset(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct charset* retval = read_complement_charset(arena, tokenizer, scope);
	#else
	struct charset* retval = read_complement_charset(tokenizer, scope);
	#endif
	
	EXIT;
	return retval;
}

