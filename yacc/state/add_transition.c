
#include <debug.h>

#include <memory/smalloc.h>
#include <memory/srealloc.h>

#include <set/unsigned/compare.h>
#include <set/unsigned/inc.h>

#include "struct.h"
#include "add_transition.h"

void yacc_state_add_transition(
	struct yacc_state* this,
	struct unsignedset* on,
	struct yacc_state* to)
{
	ENTER;
	
	struct yacc_state_transition* transition = smalloc(sizeof(*transition));
	
	transition->on = inc_unsignedset(on);
	transition->to = to;
	
	if (this->transitions.n == this->transitions.cap)
	{
		this->transitions.cap = this->transitions.cap << 1 ?: 1;
		
		dpv(this->transitions.cap);
		
		this->transitions.data = srealloc(
			this->transitions.data,
			sizeof(*this->transitions.data) * this->transitions.cap);
	}
	
	unsigned i;
	struct yacc_state_transition** const data = this->transitions.data;
	
	for (i = this->transitions.n++ - 1;
		0 + 1 <= i + 1 && compare_unsignedsets(on, data[i]->on) < 0; i--)
	{
		data[i + 1] = data[i];
	}
	
	data[i + 1] = transition;
	
	EXIT;
}

