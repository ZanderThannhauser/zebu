
#if 0
#include <debug.h>

#include <parser/grammar/gbundle.h>

#include "state/new.h"
#include "state/add_transition.h"

#include "from_token.h"

struct gbundle gegex_from_token(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	unsigned token_id)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct gegex* start = new_gegex(arena);
	struct gegex* end = new_gegex(arena);
	#else
	struct gegex* start = new_gegex();
	struct gegex* end = new_gegex();
	#endif
	
	dpv(start);
	dpv(end);
	
	gegex_add_transition(start, token_id, end);
	
	EXIT;
	return (struct gbundle) {start, end};
}
#endif
