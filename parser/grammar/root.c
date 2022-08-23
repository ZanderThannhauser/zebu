
#include <debug.h>

#include "or.h"
#include "root.h"

struct gbundle read_root_production(
	struct memory_arena* grammar_arena,
	struct memory_arena* token_arena,
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	struct gbundle inner = read_or_production(
		grammar_arena, token_arena,
		tokenizer, options, scope, lex);
	
	EXIT;
	return inner;
}

