
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
	
	#ifdef WITH_ARENAS
	struct memory_arena* const arena = this->arena;
	#endif
	
	#ifdef WITH_ARENAS
	struct regex* start = new_regex(arena);
	struct regex* end = new_regex(arena);
	#else
	struct regex* start = new_regex();
	struct regex* end = new_regex();
	#endif
	
	regex_set_EOF_transition(start, end);
	
	end->is_accepting = true;
	
	#ifdef DOTOUT
	regex_dotout(start, __PRETTY_FUNCTION__);
	#endif
	
	if (skip)
	{
		#ifdef WITH_ARENAS
		struct regex* clone = regex_clone(this->arena, skip);
		#else
		struct regex* clone = regex_clone(skip);
		#endif
		
		regex_add_lambda_transition(clone, start);
		
		#ifdef WITH_ARENAS
		struct regex* dfa = regex_nfa_to_dfa(this->arena, clone);
		#else
		struct regex* dfa = regex_nfa_to_dfa(clone);
		#endif
		
		#ifdef WITH_ARENAS
		start = regex_simplify_dfa(this->arena, dfa);
		#else
		start = regex_simplify_dfa(dfa);
		#endif
		
		free_regex(clone), free_regex(dfa);
	}
	
	unsigned tid = lex_add_token(this, start, /* is_literal: */ true);
	
	this->EOF_token_id = tid;
	
	dpv(this->EOF_token_id);
	
	EXIT;
}



















