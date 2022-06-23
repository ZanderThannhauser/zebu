
#include <debug.h>

#include "or.h"
#include "root.h"

struct bundle read_root_token_expression(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct scope* scope)
{
	struct bundle retval;
	ENTER;
	
	retval = read_or_token_expression(tokenizer, scratchpad, scope);
	
	EXIT;
	return retval;
}

