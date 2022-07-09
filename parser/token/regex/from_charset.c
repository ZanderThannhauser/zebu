
#include <debug.h>

#include "../../charset/charset/struct.h"

#include "state/struct.h"
#include "state/new.h"
#include "state/add_transition.h"
#include "state/set_default_transition.h"

#include "dotout.h"
#include "from_charset.h"

struct regex* regex_from_charset(
	struct charset* charset,
	struct memory_arena* arena)
{
	ENTER;
	
	struct regex* start = new_regex(arena);
	
	struct regex* inside = new_regex(arena);
	
	struct regex* outside;
	
	if (charset->is_complement)
		outside = new_regex(arena);
	
	for (size_t i = 0, n = charset->len; i < n; i++)
		regex_add_transition(start, arena, charset->chars[i], inside);
	
	if (charset->is_complement)
		regex_set_default_transition(start, outside);
	
	if (charset->is_complement)
		outside->is_accepting = true;
	else
		inside->is_accepting = true;
	
	#ifdef DEBUGGING
	regex_dotout(start);
	#endif
	
	EXIT;
	return start;
}











