
#include <debug.h>

#include <parser/tokenizer/struct.h>

#include <lex/regex/from_literal.h>
#include <lex/regex/dotout.h>

#include "character_literal.h"

struct rbundle read_character_literal_token_expression(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct regex* token_skip
) {
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
		.is_literal = true,
		.is_nfa = false,
		.dfa = dfa,
	};
}

