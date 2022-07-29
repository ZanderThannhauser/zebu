
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

#include "lookup/dfa_to_id.h"

#include "struct.h"
#include "add_EOF_token.h"

void lex_add_EOF_token(
	struct lex* this,
	struct memory_arena* scratchpad,
	struct regex* skip)
{
	ENTER;
	
	struct regex* start = new_regex(scratchpad);
	
	struct regex* end = new_regex(scratchpad);
	
	regex_set_EOF_transition(start, end);
	
	end->is_accepting = true;
	
	#ifdef DEBUGGING
	regex_dotout(start);
	#endif
	
	if (skip)
	{
		struct regex* clone = regex_clone(scratchpad, skip);
		
		regex_add_lambda_transition(clone, scratchpad, start);
		
		#ifdef DEBUGGING
		regex_dotout(clone);
		#endif
		
		struct regex* dfa = regex_nfa_to_dfa(clone, scratchpad);
		
		struct regex* simp = regex_simplify_dfa(dfa, scratchpad);
		
		free_regex(clone, scratchpad), free_regex(dfa, scratchpad);
		
		#ifdef DEBUGGING
		regex_dotout(simp);
		#endif
		
		start = simp;
	}
	
	unsigned tid = lex_dfa_to_id(this, start);
	
	this->EOF_token_id = tid;
	
	dpv(this->EOF_token_id);
	
	EXIT;
}



















