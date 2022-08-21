
#include <debug.h>

/*#include <memory/arena/malloc.h>*/
/*#include <memory/arena/realloc.h>*/

#include <set/of_tokens/compare.h>

#include "struct.h"
#include "add_transition.h"

struct ytransition* yacc_state_add_transition(
	struct yacc_state* from,
	struct memory_arena* arena,
	const struct tokenset* value,
	struct yacc_state* to)
{
	TODO;
	#if 0
	struct ytransition* transition = arena_malloc(arena, sizeof(*transition));
	
	transition->value = value;
	transition->to = to;
	
	if (from->transitions.n + 1 >= from->transitions.cap)
	{
		from->transitions.cap = from->transitions.cap * 2 ?: 1;
		
		dpv(from->transitions.cap );
		
		from->transitions.data = arena_realloc(
			arena, from->transitions.data,
			sizeof(*from->transitions.data) * from->transitions.cap);
	}
	
	size_t i;
	struct ytransition** const data = from->transitions.data;
	
	for (i = from->transitions.n++ - 1;
		0 + 1 <= i + 1 && compare_tokensets(value, data[i]->value) < 0; i--)
	{
		data[i + 1] = data[i];
	}
	
	data[i + 1] = transition;
	
	return transition;
	#endif
}













