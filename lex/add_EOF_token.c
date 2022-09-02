
#include <debug.h>

#include <regex/state/struct.h>
#include <regex/state/new.h>
#include <regex/clone.h>
#include <regex/state/free.h>
#include <regex/nfa_to_dfa.h>
#include <regex/simplify_dfa/simplify_dfa.h>
#include <regex/state/add_lambda_transition.h>
#include <regex/state/set_EOF_transition.h>

#include <regex/dotout.h>

#include "lookup/add_token.h"

#include "struct.h"

#include "add_EOF_token.h"

void lex_add_EOF_token(
	struct lex* this,
	struct regex* skip)
{
	ENTER;
	
	struct regex* start = new_regex();
	struct regex* end = new_regex();
	
	regex_set_EOF_transition(start, end);
	
	end->is_accepting = true;
	
	#ifdef DOTOUT
	regex_dotout(start, __PRETTY_FUNCTION__);
	#endif
	
	if (skip)
	{
		struct regex* clone = regex_clone(skip);
		
		regex_add_lambda_transition(clone, start);
		
		struct regex* dfa = regex_nfa_to_dfa(clone);
		
		start = regex_simplify_dfa(dfa);
		
		#ifdef DOTOUT
		regex_dotout(start, __PRETTY_FUNCTION__);
		#endif
		
		free_regex(clone), free_regex(dfa);
	}
	
	unsigned tid = lex_add_token(this, start, /* is_literal: */ true);
	
	this->EOF_token_id = tid;
	
	dpv(this->EOF_token_id);
	
	EXIT;
}


















