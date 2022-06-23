
#include <debug.h>

#include "or.h"
#include "root.h"

struct bundle read_root_production(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	struct bundle inner = read_or_production(tokenizer, scratchpad, scope, lex);
	
	EXIT;
	return inner;
}

