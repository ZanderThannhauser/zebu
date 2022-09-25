
#include <assert.h>

#include <debug.h>

#include <parser/tokenizer/struct.h>

#include <regex/from_literal.h>
#include <regex/dotout.h>

#include "character_literal.h"

struct rbundle read_character_literal_token_expression(
	struct tokenizer* tokenizer)
{
	ENTER;
	
	unsigned char code = tokenizer->tokenchars.chars[0];
	
	dpvc(code);
	
	struct regex* start = regex_from_literal(&code, 1);
	
	#ifdef DOTOUT
	regex_dotout(start, __PRETTY_FUNCTION__);
	#endif
	
	EXIT;
	return (struct rbundle) {start, NULL};
}

