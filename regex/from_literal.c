
#include <assert.h>

#include <debug.h>

#include "state/new.h"
#include "state/struct.h"

#include "dotout.h"
#include "from_literal.h"

struct regex* regex_from_literal(const unsigned char* string, unsigned len)
{
	ENTER;
	
	dpvsn(string, len);
	
	assert(len);
	
	struct regex* start = new_regex();
	
	struct regex* accept = start;
	
	while (len--)
	{
		struct regex* temp = new_regex();
		
		accept->transitions[*string++] = temp;
		
		accept = temp;
	}
	
	accept->is_accepting = true;
	
	#ifdef DOTOUT
	regex_dotout(start, __PRETTY_FUNCTION__);
	#endif
	
	EXIT;
	return start;
}











