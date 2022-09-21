
#include <debug.h>

#include <memory/srealloc.h>

#include <string/compare.h>

#include "struct.h"
#include "add_grammar_transition.h"

#include "grammar/struct.h"
#include "grammar/new.h"

void gegex_add_grammar_transition(
	struct gegex* this,
	struct string* grammar,
	struct structinfo* structinfo,
	struct gegex* to)
{
	ENTER;
	
	struct gegex_grammar_transition* transition = new_gegex_grammar_transition(
		grammar, structinfo, to);
	
	if (this->grammars.n + 1 > this->grammars.cap)
	{
		this->grammars.cap = this->grammars.cap * 2 ?: 1;
		
		this->grammars.data = srealloc(this->grammars.data,
			sizeof(*this->grammars.data) * this->grammars.cap);
	}
	
	unsigned i;
	struct gegex_grammar_transition** const gdata = this->grammars.data;
	
	for (i = this->grammars.n++ - 1; 0 + 1 <= i + 1 &&
		compare_strings(grammar, gdata[i]->grammar) < 0; i--)
	{
		gdata[i + 1] = gdata[i];
	}
	
	gdata[i + 1] = transition;
	
	EXIT;
}

