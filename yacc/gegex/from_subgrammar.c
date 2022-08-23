
#include <debug.h>

#include "state/new.h"
#include "state/add_grammar_transition.h"

#include "from_subgrammar.h"

struct gbundle gegex_from_subgrammar(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	char* grammar_name)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct gegex* start = new_gegex(arena);
	struct gegex* end = new_gegex(arena);
	#else
	struct gegex* start = new_gegex();
	struct gegex* end = new_gegex();
	#endif
	
	gegex_add_grammar_transition(start, grammar_name, end);
	
	EXIT;
	return (struct gbundle) {start, end};
}

