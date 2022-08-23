
#include <debug.h>

#include "or.h"
#include "root.h"

struct rbundle read_root_token_expression(
	struct memory_arena* arena,
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct regex* token_skip)
{
	struct rbundle retval;
	ENTER;
	
	retval = read_or_token_expression(arena, tokenizer, scope, token_skip);
	
	EXIT;
	return retval;
}

