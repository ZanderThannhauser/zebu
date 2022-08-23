
#include <string.h>

#include <debug.h>

#include <arena/malloc.h>
#include <arena/realloc.h>

#include "struct.h"
#include "add_grammar_transition.h"

struct gytransition* yacc_state_add_grammar_transition(
	struct yacc_state* from,
	const char* grammar,
	struct yacc_state* to)
{
	ENTER;
	
	struct memory_arena* const arena = from->arena;
	
	struct gytransition* gtransition = arena_malloc(arena, sizeof(*gtransition));
	
	gtransition->grammar = grammar;
	gtransition->to = to;
	
	if (from->grammar_transitions.n + 1 > from->grammar_transitions.cap)
	{
		from->grammar_transitions.cap = from->grammar_transitions.cap * 2 ?: 1;
		
		dpv(from->grammar_transitions.cap);
		
		from->grammar_transitions.data = arena_realloc(
			arena, from->grammar_transitions.data,
			sizeof(*from->grammar_transitions.data) * from->grammar_transitions.cap);
	}
	
	size_t i;
	struct gytransition** const gdata = from->grammar_transitions.data;
	
	for (i = from->grammar_transitions.n++ - 1;
		0 + 1 <= i + 1 && strcmp(grammar, gdata[i]->grammar) < 0; i--)
	{
		gdata[i + 1] = gdata[i];
	}
	
	gdata[i + 1] = gtransition;
	
	EXIT;
	return gtransition;
}














