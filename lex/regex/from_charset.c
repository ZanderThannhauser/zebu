
#include <debug.h>

#include <parser/charset/charset/struct.h>

#include "state/struct.h"
#include "state/new.h"
#include "state/add_transition.h"
#include "state/set_default_transition.h"

#include "dotout.h"
#include "from_charset.h"

struct regex* regex_from_charset(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct charset* charset)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct regex* start = new_regex(arena);
	struct regex* inside = new_regex(arena);
	#else
	struct regex* start = new_regex();
	struct regex* inside = new_regex();
	#endif
	
	struct regex* outside;
	
	if (charset->is_complement)
	{
		#ifdef WITH_ARENAS
		outside = new_regex(arena);
		#else
		outside = new_regex();
		#endif
	}
	
	for (size_t i = 0, n = charset->len; i < n; i++)
		regex_add_transition(start, charset->chars[i], inside);
	
	if (charset->is_complement)
		regex_set_default_transition(start, outside);
	
	if (charset->is_complement)
		outside->is_accepting = true;
	else
		inside->is_accepting = true;
	
	#ifdef DEBUGGING
	regex_dotout(start, __PRETTY_FUNCTION__);
	#endif
	
	EXIT;
	return start;
}











