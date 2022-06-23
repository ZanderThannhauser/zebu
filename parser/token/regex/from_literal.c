
#include <debug.h>

#include "state/struct.h"
#include "state/new.h"
#include "state/add_transition.h"

#include "dotout.h"
#include "from_literal.h"

struct regex* regex_from_literal(
	struct memory_arena* arena,
	const char* string,
	size_t len)
{
	ENTER;
	
	dpvsn(string, len);
	
	struct regex* start = new_regex(arena);
	
	dpv(start);
	
	struct regex* accept = start;
	
	while (len--)
	{
		struct regex* temp = new_regex(arena);
		
		regex_add_transition(accept, arena, (unsigned) *string++, temp);
		
		accept = temp;
	}
	
	accept->is_accepting = true;
	
	#ifdef DEBUGGING
	regex_dotout(start);
	#endif
	
	EXIT;
	return start;
}












