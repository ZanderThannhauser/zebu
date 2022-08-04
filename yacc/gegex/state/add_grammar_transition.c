
#include <string.h>

#include <debug.h>

/*#include <memory/arena/strdup.h>*/
#include <memory/arena/malloc.h>
#include <memory/arena/realloc.h>

#include "struct.h"
#include "add_grammar_transition.h"

void gegex_add_grammar_transition(
	struct gegex* from,
	struct memory_arena* arena,
	char* grammar_name,
	struct gegex* to)
{
	ENTER;
	
	struct gtransition* gtransition = arena_malloc(arena, sizeof(*gtransition));
	
	dpv(gtransition);
	
	gtransition->grammar = grammar_name;
	// gtransition->start = NULL;
	gtransition->to = to;
	
	if (from->grammar_transitions.n + 1 > from->grammar_transitions.cap)
	{
		from->grammar_transitions.cap = from->grammar_transitions.cap * 2 ?: 1;
		
		from->grammar_transitions.data = arena_realloc(
			arena, from->grammar_transitions.data,
			sizeof(*from->grammar_transitions.data) * from->grammar_transitions.cap);
	}
	
	size_t i;
	struct gtransition** const gdata = from->grammar_transitions.data;
	
	for (i = from->grammar_transitions.n++ - 1;
		0 + 1 <= i + 1 && strcmp(grammar_name, gdata[i]->grammar) < 0; i--)
	{
		gdata[i + 1] = gdata[i];
	}
	
	gdata[i + 1] = gtransition;
	
	EXIT;
}












