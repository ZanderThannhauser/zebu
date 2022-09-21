
#include <debug.h>

#include <parser/tokenizer/struct.h>

#include <regex/dotout.h>
#include <regex/from_literal.h>

#include "string_literal.h"

struct rbundle read_string_literal_token_expression(
	struct tokenizer* tokenizer,
	struct scope* scope
) {
	ENTER;
	
	dpvsn(tokenizer->tokenchars.chars, tokenizer->tokenchars.n);
	
	struct regex* start = regex_from_literal(
		/* chars:      */ tokenizer->tokenchars.chars,
		/* strlen:     */ tokenizer->tokenchars.n);
	
	#ifdef DOTOUT
	regex_dotout(start, __PRETTY_FUNCTION__);
	#endif
	
	EXIT;
	return (struct rbundle) {
		.is_nfa = false,
		.dfa = start,
	};
}
