
#include <debug.h>

#include "or.h"
#include "root.h"

struct gbundle read_root_production(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	struct gbundle inner = read_or_production(tokenizer, scratchpad, scope, lex);
	
	EXIT;
	return inner;
}

