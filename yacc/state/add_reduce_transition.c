
#include <debug.h>

#include <memory/arena/malloc.h>
#include <memory/arena/realloc.h>

#include <set/of_tokens/compare.h>

#include "struct.h"
#include "add_reduce_transition.h"

void yacc_state_add_reduce_transition(
	struct yacc_state* from,
	struct memory_arena* arena,
	const struct tokenset* value,
	const char* reduce_as,
	unsigned popcount)
{
	struct rytransition* transition = arena_malloc(arena, sizeof(*transition));
	
	transition->value = value;
	transition->reduce_as = reduce_as;
	transition->popcount = popcount;
	
	if (from->reduction_transitions.n + 1 >= from->reduction_transitions.cap)
	{
		from->reduction_transitions.cap = from->reduction_transitions.cap * 2 ?: 1;
		
		dpv(from->reduction_transitions.cap );
		
		from->reduction_transitions.data = arena_realloc(
			arena, from->reduction_transitions.data,
			sizeof(*from->reduction_transitions.data) * from->reduction_transitions.cap);
	}
	
	size_t i;
	struct rytransition** const data = from->reduction_transitions.data;
	
	for (i = from->reduction_transitions.n++ - 1;
		0 + 1 <= i + 1 && compare_tokensets(value, data[i]->value) < 0; i--)
	{
		data[i + 1] = data[i];
	}
	
	data[i + 1] = transition;
}













