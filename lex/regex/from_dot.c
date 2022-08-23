
#include <debug.h>

#include "state/struct.h"
#include "state/new.h"
#include "state/set_default_transition.h"

#include "from_dot.h"

struct regex* regex_from_dot(
	#ifdef WITH_ARENAS
	struct memory_arena* arena
	#endif
) {
	ENTER;
	
	#ifdef WITH_ARENAS
	struct regex* start = new_regex(arena);
	struct regex* end = new_regex(arena);
	#else
	struct regex* start = new_regex();
	struct regex* end = new_regex();
	#endif
	
	regex_set_default_transition(start, end);
	
	end->is_accepting = true;
	
	EXIT;
	return start;
}

