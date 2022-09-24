
#include <debug.h>

#include <parser/tokenizer/struct.h>

#include <regex/from_literal.h>
#include <regex/dotout.h>

#include "character_literal.h"

struct rbundle read_character_literal_token_expression(
	struct tokenizer* tokenizer)
{
	ENTER;
	
	dpvc(tokenizer->tokenchars.chars[0]);
	
	struct regex* dfa = regex_from_literal(
		/* chars:  */ tokenizer->tokenchars.chars,
		/* strlen: */ 1);
	
	#ifdef DOTOUT
	regex_dotout(dfa, __PRETTY_FUNCTION__);
	#endif
	
	EXIT;
	return (struct rbundle) {
		.is_nfa = false,
		.dfa = dfa,
	};
}

