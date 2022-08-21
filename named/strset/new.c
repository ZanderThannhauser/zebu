
/*#include <memory/smalloc.h>*/

#include <debug.h>

#include "struct.h"
#include "new.h"

struct named_strset* new_named_strset(const char* name, struct strset* strset)
{
	ENTER;
	
	dpvs(name);
	
	TODO;
	#if 0
	struct named_strset* new = smalloc(sizeof(*new));
	
	new->name = name;
	new->strset = strset;
	
	EXIT;
	return new;
	#endif
}

