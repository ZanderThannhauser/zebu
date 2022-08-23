
#include <stdlib.h>

#include <arena/malloc.h>

#include <debug.h>

#include "struct.h"
#include "new.h"

struct named_strset* new_named_strset(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	const char* name, struct strset* strset)
{
	ENTER;
	
	dpvs(name);
	
	#ifdef WITH_ARENAS
	struct named_strset* new = arena_malloc(arena, sizeof(*new));
	#else
	struct named_strset* new = malloc(sizeof(*new));
	#endif
	
	new->name = name;
	new->strset = strset;
	
	EXIT;
	return new;
}

