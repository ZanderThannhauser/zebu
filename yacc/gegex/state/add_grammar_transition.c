
#if 0
#include <stdlib.h>
#include <string.h>

#include <debug.h>

/*#include <memory/arena/strdup.h>*/
#include <arena/malloc.h>
#include <arena/realloc.h>

#include "struct.h"
#include "add_grammar_transition.h"

void gegex_add_grammar_transition(
	struct gegex* from,
	char* grammar_name,
	struct gegex* to)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct memory_arena* const arena = from->arena;
	struct gtransition* gtransition = arena_malloc(arena, sizeof(*gtransition));
	#else
	struct gtransition* gtransition = malloc(sizeof(*gtransition));
	#endif
	
	dpv(gtransition);
	
	gtransition->grammar = grammar_name;
	// gtransition->start = NULL;
	gtransition->to = to;
	
	if (from->grammar_transitions.n + 1 > from->grammar_transitions.cap)
	{
		from->grammar_transitions.cap = from->grammar_transitions.cap * 2 ?: 1;
		
		#ifdef WITH_ARENAS
		from->grammar_transitions.data = arena_realloc(
			arena, from->grammar_transitions.data,
			sizeof(*from->grammar_transitions.data) * from->grammar_transitions.cap);
		#else
		from->grammar_transitions.data = realloc(from->grammar_transitions.data,
			sizeof(*from->grammar_transitions.data) * from->grammar_transitions.cap);
		#endif
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











#endif
