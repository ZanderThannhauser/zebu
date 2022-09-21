
#include <debug.h>

#include <memory/smalloc.h>

#include <string/inc.h>

#include <yacc/structinfo/inc.h>

#include "struct.h"
#include "new.h"

struct gegex_grammar_transition* new_gegex_grammar_transition(
	struct string* grammar,
	struct structinfo* structinfo,
	struct gegex* to)
{
	ENTER;
	
	struct gegex_grammar_transition* transition = smalloc(sizeof(*transition));
	
	transition->grammar = inc_string(grammar);
	transition->structinfo = inc_structinfo(structinfo);
	transition->to = to;
	
	EXIT;
	return transition;
}

