
#include <stdlib.h>
#include <string.h>

#include <debug.h>

#include <set/string/inc.h>

#include "struct.h"
#include "add_grammar_transition.h"

void gegex_add_grammar_transition(
	struct gegex* from,
	struct string* grammar_name,
	struct stringset* tags,
	struct gegex* to)
{
	ENTER;
	
	struct gegex_grammar_transition* gtransition = smalloc(sizeof(*gtransition));
	
	gtransition->grammar = inc_string(grammar_name);
	gtransition->tags = inc_stringset(tags);
	gtransition->to = to;
	
	if (from->grammar_transitions.n + 1 > from->grammar_transitions.cap)
	{
		from->grammar_transitions.cap = from->grammar_transitions.cap * 2 ?: 1;
		
		from->grammar_transitions.data = realloc(from->grammar_transitions.data, sizeof(*from->grammar_transitions.data) * from->grammar_transitions.cap);
	}
	
	unsigned i;
	struct gegex_grammar_transition** const gdata = from->grammar_transitions.data;
	
	for (i = from->grammar_transitions.n++ - 1; 0 + 1 <= i + 1 && compare_strings(grammar_name, gdata[i]->grammar) < 0; i--)
	{
		gdata[i + 1] = gdata[i];
	}
	
	gdata[i + 1] = gtransition;
	
	EXIT;
}











