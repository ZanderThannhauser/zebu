
#include <debug.h>

#include "state/new.h"
#include "state/struct.h"
#include "state/add_transition.h"

#include "dotout.h"
#include "from_literal.h"

struct regex* regex_from_literal(
	const unsigned char* string,
	size_t len
) {
	ENTER;
	
	dpvsn(string, len);
	
	struct regex* start = new_regex();
	
	dpv(start);
	
	struct regex* accept = start;
	
	while (len--)
	{
		struct regex* temp = new_regex();
		
		regex_add_transition(accept, *string++, temp);
		
		accept = temp;
	}
	
	accept->is_accepting = true;
	
	#ifdef DOTOUT
	regex_dotout(start, __PRETTY_FUNCTION__);
	#endif
	
	EXIT;
	return start;
}











