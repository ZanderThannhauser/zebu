
#include <stddef.h>

#include <debug.h>

#include <regex/from_dot.h>
#include <regex/dotout.h>

#include "dot.h"

struct rbundle read_dot_token_expression(
	struct tokenizer* tokenizer)
{
	ENTER;
	
	struct regex* start = regex_from_dot();
	
	#ifdef DOTOUT
	regex_dotout(start, __PRETTY_FUNCTION__);
	#endif
	
	EXIT;
	return (struct rbundle) {start, NULL};
}
