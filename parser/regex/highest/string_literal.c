
#include <debug.h>

#include <parser/tokenizer/struct.h>

#include <regex/from_literal.h>

#include "string_literal.h"

struct rbundle read_string_literal_token_expression(
	struct tokenizer* tokenizer)
{
	ENTER;
	
	dpvsn(tokenizer->tokenchars.chars, tokenizer->tokenchars.n);
	
	struct regex* start = regex_from_literal(
		/* chars:  */ tokenizer->tokenchars.chars,
		/* strlen: */ tokenizer->tokenchars.n);
	
	EXIT;
	return (struct rbundle) {start, NULL};
}
