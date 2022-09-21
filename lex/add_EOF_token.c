
#include <debug.h>

#include <regex/struct.h>
#include <regex/new.h>
/*#include <regex/clone.h>*/
/*#include <regex/state/free.h>*/
/*#include <regex/nfa_to_dfa.h>*/
/*#include <regex/simplify_dfa/simplify_dfa.h>*/
/*#include <regex/state/add_lambda_transition.h>*/

#include <regex/dotout.h>

#include "add_token.h"

#include "struct.h"

#include "add_EOF_token.h"

void lex_add_EOF_token(struct lex* this)
{
	ENTER;
	
	struct regex* start = new_regex();
	struct regex* end = new_regex();
	
	start->EOF_transition_to = end;
	
	end->accepts = true;
	
	#ifdef DOTOUT
	regex_dotout(start, __PRETTY_FUNCTION__);
	#endif
	
	unsigned tid = lex_add_token(this, start, tk_literal);
	
	this->EOF_token_id = tid;
	
	dpv(this->EOF_token_id);
	
	EXIT;
}


















