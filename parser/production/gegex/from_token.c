
#include <debug.h>

#include "../bundle.h"

#include "state/new.h"
#include "state/add_transition.h"

#include "from_token.h"

struct bundle gegex_from_token(
	struct memory_arena* arena,
	unsigned token_id)
{
	ENTER;
	
	struct gegex* start = new_gegex(arena);
	struct gegex* end = new_gegex(arena);
	
	gegex_add_transition(start, arena, token_id, end);
	
	EXIT;
	return (struct bundle) {start, end};
}
