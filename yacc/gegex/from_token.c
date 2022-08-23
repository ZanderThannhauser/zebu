
#include <debug.h>

#include <parser/grammar/gbundle.h>

#include "state/new.h"
#include "state/add_transition.h"

#include "from_token.h"

struct gbundle gegex_from_token(
	struct memory_arena* arena,
	unsigned token_id)
{
	ENTER;
	
	struct gegex* start = new_gegex(arena);
	struct gegex* end = new_gegex(arena);
	
	dpv(start);
	dpv(end);
	
	gegex_add_transition(start, token_id, end);
	
	EXIT;
	return (struct gbundle) {start, end};
}
