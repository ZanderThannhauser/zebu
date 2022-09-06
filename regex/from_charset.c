
#include <debug.h>

#include "state/struct.h"
#include "state/new.h"

#include "dotout.h"
#include "from_charset.h"

struct regex* regex_from_charset(charset_t charset)
{
	ENTER;
	
	struct regex* start = new_regex();
	
	struct regex* accept = new_regex();
	
	accept->is_accepting = true;
	
	for (unsigned i = 0, n = 256; i < n; i++)
		if (charset[i >> 4] & 1 << (i & 0xF))
			start->transitions[i] = accept;
	
	#ifdef DOTOUT
	regex_dotout(start, __PRETTY_FUNCTION__);
	#endif
	
	EXIT;
	return start;
}

















