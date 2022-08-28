
#include <debug.h>

#include <charset/struct.h>

#include "state/struct.h"
#include "state/new.h"
#include "state/add_transition.h"
#include "state/set_default_transition.h"

#include "dotout.h"
#include "from_charset.h"

struct regex* regex_from_charset(
	struct charset* charset)
{
	ENTER;
	
	struct regex* start = new_regex();
	struct regex* inside = new_regex();
	
	struct regex* outside;
	
	if (charset->is_complement)
	{
		outside = new_regex();
	}
	
	for (size_t i = 0, n = charset->len; i < n; i++)
		regex_add_transition(start, charset->chars[i], inside);
	
	if (charset->is_complement)
		regex_set_default_transition(start, outside);
	
	if (charset->is_complement)
		outside->is_accepting = true;
	else
		inside->is_accepting = true;
	
	#ifdef DOTOUT
	regex_dotout(start, __PRETTY_FUNCTION__);
	#endif
	
	EXIT;
	return start;
}







