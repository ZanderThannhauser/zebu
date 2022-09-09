
#include <debug.h>

#include <memory/smalloc.h>
#include <memory/srealloc.h>

#include <string/inc.h>
#include <string/compare.h>

#include "struct.h"
#include "add_grammar_transition.h"

void yacc_state_add_grammar_transition(
	struct yacc_state* this,
	struct string* grammar,
	struct yacc_state* to)
{
	ENTER;
	
	struct yacc_state_grammar_transition* transition = smalloc(sizeof(*transition));
	
	transition->grammar = inc_string(grammar);
	transition->to = to;
	
	if (this->grammar_transitions.n == this->grammar_transitions.cap)
	{
		this->grammar_transitions.cap = this->grammar_transitions.cap << 1 ?: 1;
		
		dpv(this->grammar_transitions.cap);
		
		this->grammar_transitions.data = srealloc(
			this->grammar_transitions.data,
			sizeof(*this->grammar_transitions.data) * this->grammar_transitions.cap);
	}
	
	unsigned i;
	struct yacc_state_grammar_transition** const data = this->grammar_transitions.data;
	
	for (i = this->grammar_transitions.n++ - 1;
		0 + 1 <= i + 1 && compare_strings(grammar, data[i]->grammar) < 0; i--)
	{
		data[i + 1] = data[i];
	}
	
	data[i + 1] = transition;
	
	EXIT;
}
