
#include <arena/malloc.h>

#include <debug.h>

#include "struct.h"
#include "new.h"

struct named_strset* new_named_strset(
	struct memory_arena* arena,
	const char* name, struct strset* strset)
{
	ENTER;
	
	dpvs(name);
	
	struct named_strset* new = arena_malloc(arena, sizeof(*new));
	
	new->name = name;
	new->strset = strset;
	
	EXIT;
	return new;
}

