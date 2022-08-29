
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "add_transition.h"

void regex_add_transition(
	struct regex* from,
	unsigned char value,
	struct regex* to
) {
	ENTER;
	
	dpv(value);
	dpv(from);
	dpv(to);
	
	struct regex_transition* transition = smalloc(sizeof(*transition));
	
	transition->value = value;
	transition->to = to;
	
	if (from->transitions.n + 1 > from->transitions.cap)
	{
		from->transitions.cap = from->transitions.cap * 2 ?: 1;
		
		dpv(from->transitions.cap);
		
		from->transitions.data = srealloc(from->transitions.data,
			sizeof(*from->transitions.data) * from->transitions.cap);
	}
	
	unsigned i;
	struct regex_transition** const data = from->transitions.data;
	
	dpv(data);
	
	dpv(from->transitions.n);
	
	for (i = from->transitions.n - 1; 0 + 1 <= i + 1 && value < data[i]->value; i--)
	{
		dpv(i);
		
		data[i + 1] = data[i];
	}
	
	dpv(i);
	
	data[i + 1] = transition, from->transitions.n++;

	EXIT;
}


















