
#include <debug.h>

#include <parser/tokenizer/struct.h>

#include <lex/regex/from_literal.h>

#include "string_literal.h"

struct rbundle read_string_literal_token_expression(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct regex* token_skip
) {
	ENTER;
	
	dpvsn(tokenizer->tokenchars.chars, tokenizer->tokenchars.n);
	
	struct regex* dfa = regex_from_literal(
		/* chars:      */ tokenizer->tokenchars.chars,
		/* strlen:     */ tokenizer->tokenchars.n);
	
	EXIT;
	return (struct rbundle) {
		.is_literal = true,
		.is_nfa = false,
		.dfa = dfa,
	};
}
