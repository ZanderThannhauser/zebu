
#include <debug.h>

#include "struct.h"
#include "add_grammar_transition.h"

void trie_add_grammar_transition(
	struct trie* this,
	struct string* grammar,
	struct trie* to)
{
	ENTER;
	
	struct trie_grammar_transition* gtransition = smalloc(sizeof(*gtransition));
	
	gtransition->grammar = inc_string(grammar);
	gtransition->to = to;
	
	if (this->grammar_transitions.n + 1 > this->grammar_transitions.cap)
	{
		this->grammar_transitions.cap = this->grammar_transitions.cap * 2 ?: 1;
		
		this->grammar_transitions.data = srealloc(this->grammar_transitions.data,
			sizeof(*this->grammar_transitions.data) * this->grammar_transitions.cap);
	}
	
	unsigned i;
	struct trie_grammar_transition** const gdata = this->grammar_transitions.data;
	
	for (i = this->grammar_transitions.n++ - 1; 0 + 1 <= i + 1 && compare_strings(grammar, gdata[i]->grammar) < 0; i--)
	{
		gdata[i + 1] = gdata[i];
	}
	
	gdata[i + 1] = gtransition;
	
	EXIT;
}

