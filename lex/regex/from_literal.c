
#include <debug.h>

#include "state/struct.h"
#include "state/new.h"
#include "state/add_transition.h"

#include "dotout.h"
#include "from_literal.h"

struct regex* regex_from_literal(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	const char* string,
	size_t len)
{
	ENTER;
	
	dpvsn(string, len);
	
	#ifdef WITH_ARENAS
	struct regex* start = new_regex(arena);
	#else
	struct regex* start = new_regex();
	#endif
	
	dpv(start);
	
	struct regex* accept = start;
	
	while (len--)
	{
		#ifdef WITH_ARENAS
		struct regex* temp = new_regex(arena);
		#else
		struct regex* temp = new_regex();
		#endif
		
		regex_add_transition(accept, (unsigned) *string++, temp);
		
		accept = temp;
	}
	
	accept->is_accepting = true;
	
	#ifdef DEBUGGING
	regex_dotout(start, __PRETTY_FUNCTION__);
	#endif
	
	EXIT;
	return start;
}












