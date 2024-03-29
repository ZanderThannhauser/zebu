
#if 0

#include <debug.h>

#include <parser/production/gbundle.h>

#include "state/new.h"
#include "state/add_transition.h"

#include "from_token.h"

struct gbundle gegex_from_token(unsigned token_id)
{
	ENTER;
	
	struct gegex* start = new_gegex();
	struct gegex* end = new_gegex();
	
	dpv(start);
	dpv(end);
	
	gegex_add_transition(start, token_id, end);
	
	EXIT;
	return (struct gbundle) {start, end};
}

#endif
