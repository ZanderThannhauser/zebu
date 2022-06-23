
#include <debug.h>

#include "state/new.h"
#include "state/add_grammar_transition.h"

#include "from_subgrammar.h"

struct bundle gegex_from_subgrammar(
	char* grammar_name,
	struct memory_arena* arena)
{
	ENTER;
	
	struct gegex* start = new_gegex(arena);
	
	struct gegex* end = new_gegex(arena);
	
	gegex_add_grammar_transition(start, arena, grammar_name, end);
	
	EXIT;
	return (struct bundle) {start, end};
}

