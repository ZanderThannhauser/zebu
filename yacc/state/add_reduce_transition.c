
#include <debug.h>

#include <set/unsigned/compare.h>
#include <set/unsigned/inc.h>

#include <yacc/reductioninfo/inc.h>

#include <yacc/structinfo/inc.h>

#include "struct.h"
#include "add_reduce_transition.h"

void yacc_state_add_reduce_transition(
	struct yacc_state* this,
	struct unsignedset* on,
	struct string* reduce_as,
	struct reductioninfo* reductioninfo,
	struct structinfo* structinfo)
{
	ENTER;
	
	struct yacc_state_reduce_transition* transition = smalloc(sizeof(*transition));
	
	transition->on = inc_unsignedset(on);
	transition->reduce_as = inc_string(reduce_as);
	transition->reductioninfo = inc_reductioninfo(reductioninfo);
	transition->structinfo = inc_structinfo(structinfo);
	
	if (this->reduce_transitions.n == this->reduce_transitions.cap)
	{
		this->reduce_transitions.cap = this->reduce_transitions.cap << 1 ?: 1;
		
		dpv(this->reduce_transitions.cap);
		
		this->reduce_transitions.data = srealloc(
			this->reduce_transitions.data,
			sizeof(*this->reduce_transitions.data) * this->reduce_transitions.cap);
	}
	
	unsigned i;
	struct yacc_state_reduce_transition** const data = this->reduce_transitions.data;
	
	for (i = this->reduce_transitions.n++ - 1;
		0 + 1 <= i + 1 && compare_unsignedsets(on, data[i]->on) < 0; i--)
	{
		data[i + 1] = data[i];
	}
	
	data[i + 1] = transition;
	
	EXIT;
}

