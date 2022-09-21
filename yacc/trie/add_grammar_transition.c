
#include <debug.h>

#include <memory/smalloc.h>
#include <memory/srealloc.h>

#include <string/inc.h>
#include <string/compare.h>

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
	
	if (this->grammars.n + 1 > this->grammars.cap)
	{
		this->grammars.cap = this->grammars.cap * 2 ?: 1;
		
		this->grammars.data = srealloc(this->grammars.data,
			sizeof(*this->grammars.data) * this->grammars.cap);
	}
	
	unsigned i;
	struct trie_grammar_transition** const gdata = this->grammars.data;
	
	for (i = this->grammars.n++ - 1; 0 + 1 <= i + 1 && compare_strings(grammar, gdata[i]->grammar) < 0; i--)
	{
		gdata[i + 1] = gdata[i];
	}
	
	gdata[i + 1] = gtransition;
	
	EXIT;
}

