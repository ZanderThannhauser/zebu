
#include <debug.h>

#include <lex/regex/state/struct.h>
#include <lex/regex/state/new.h>
#include <lex/regex/clone.h>
#include <lex/regex/state/free.h>
#include <lex/regex/nfa_to_dfa/nfa_to_dfa.h>
#include <lex/regex/simplify_dfa/simplify_dfa.h>
#include <lex/regex/state/add_lambda_transition.h>
#include <lex/regex/state/set_EOF_transition.h>

#include <lex/regex/dotout.h>

#include "lookup/add_token.h"

#include "struct.h"
#include "add_EOF_token.h"

void lex_add_EOF_token(
	struct lex* this,
	struct regex* skip)
{
	ENTER;
	
	struct memory_arena* const arena = this->arena;
	
	struct regex* start = new_regex(arena);
	
	struct regex* end = new_regex(arena);
	
	regex_set_EOF_transition(start, end);
	
	end->is_accepting = true;
	
	#ifdef DEBUGGING
	regex_dotout(start, __PRETTY_FUNCTION__);
	#endif
	
	if (skip)
	{
		struct regex* clone = regex_clone(skip, this->arena);
		
		regex_add_lambda_transition(clone, start);
		
		struct regex* dfa = regex_nfa_to_dfa(clone, this->arena);
		
		start = regex_simplify_dfa(dfa, this->arena);
		
		free_regex(clone), free_regex(dfa);
	}
	
	unsigned tid = lex_add_token(this, start, /* is_literal: */ true);
	
	this->EOF_token_id = tid;
	
	dpv(this->EOF_token_id);
	
	EXIT;
}



















