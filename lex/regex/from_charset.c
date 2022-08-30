
#include <debug.h>

#include <set/unsignedchar/foreach.h>

#include "state/struct.h"
#include "state/new.h"
#include "state/add_transition.h"
#include "state/set_default_transition.h"

#include "dotout.h"
#include "from_charset.h"

struct regex* regex_from_charset(
	bool is_complement,
	struct unsignedcharset* charset)
{
	ENTER;
	
	struct regex* start = new_regex();
	
	struct regex* accepting = new_regex();
	
	accepting->is_accepting = true;
	
	if (is_complement)
	{
		regex_set_default_transition(start, charset, accepting);
	}
	else
	{
		unsignedcharset_foreach(charset, ({
			void runme(unsigned char value)
			{
				regex_add_transition(start, value, accepting);
			}
			runme;
		}));
	}
	
	#ifdef DOTOUT
	regex_dotout(start, __PRETTY_FUNCTION__);
	#endif
	
	EXIT;
	return start;
}







