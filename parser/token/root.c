
#include <debug.h>

#include "or.h"
#include "root.h"

struct rbundle read_root_token_expression(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct regex* token_skip)
{
	struct rbundle retval;
	ENTER;
	
	#ifdef WITH_ARENAS
	retval = read_or_token_expression(arena, tokenizer, scope, token_skip);
	#else
	retval = read_or_token_expression(tokenizer, scope, token_skip);
	#endif
	
	EXIT;
	return retval;
}

