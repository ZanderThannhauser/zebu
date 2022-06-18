
#include <debug.h>

#include "or.h"
#include "root.h"

struct bundle read_root_token_expression(
	struct memory_arena* scratchpad,
	struct tokenizer* tokenizer)
{
	struct bundle retval;
	ENTER;
	
	retval = read_or_token_expression(scratchpad, tokenizer);
	
	EXIT;
	return retval;
}

