
#include <stdlib.h>

#include <debug.h>

#include "struct.h"

#include "add_transition.h"

void lex_state_add_transition(
	struct lex_state* from,
	unsigned char value,
	struct lex_state* to)
{
	ENTER;
	
	struct lex_transition* transition = smalloc(sizeof(*transition));
	
	dpv(transition);
	
	transition->value = value;
	transition->to = to;
	
	if (from->transitions.n == from->transitions.cap)
	{
		from->transitions.cap = from->transitions.cap << 1 ?: 1;
		
		dpv(from->transitions.cap);
		
		from->transitions.data = srealloc(from->transitions.data,
			sizeof(*from->transitions.data) * from->transitions.cap);
	}
	
	size_t i;
	struct lex_transition** const data = from->transitions.data;
	
	for (i = from->transitions.n++ - 1;
		0 + 1 <= i + 1 && value < data[i]->value; i--)
	{
		data[i + 1] = data[i];
	}
	
	data[i + 1] = transition;
	
	EXIT;
}
