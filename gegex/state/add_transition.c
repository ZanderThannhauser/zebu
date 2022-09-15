
#include <stdlib.h>
#include <debug.h>

#include <memory/smalloc.h>
#include <memory/srealloc.h>

#include <yacc/structinfo/inc.h>

#include <set/unsigned/inc.h>

#include "struct.h"
#include "add_transition.h"

void gegex_add_transition(
	struct gegex* from,
	unsigned token,
	struct unsignedset* whitespace,
	struct structinfo* structinfo,
	struct gegex* to)
{
	ENTER;
	
	struct gegex_transition* transition = smalloc(sizeof(*transition));
	
	transition->token = token;
	transition->whitespace = inc_unsignedset(whitespace);
	transition->structinfo = inc_structinfo(structinfo);
	transition->to = to;
	
	if (from->transitions.n + 1 > from->transitions.cap)
	{
		from->transitions.cap = from->transitions.cap * 2 ?: 1;
		
		dpv(from->transitions.cap);
		
		from->transitions.data = srealloc(from->transitions.data, sizeof(*from->transitions.data) * from->transitions.cap);
	}
	
	unsigned i;
	struct gegex_transition** const data = from->transitions.data;
	
	for (i = from->transitions.n++ - 1; 0 + 1 <= i + 1 && token < data[i]->token; i--)
	{
		data[i + 1] = data[i];
	}
	
	data[i + 1] = transition;
	
	EXIT;
}



















