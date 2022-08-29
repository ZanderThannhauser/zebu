
#include <debug.h>

#include <lex/regex/from_dot.h>
#include <lex/regex/dotout.h>

#include "dot.h"

struct rbundle read_dot_token_expression(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct regex* token_skip
) {
	ENTER;
	
	struct regex* regex = regex_from_dot();
	
	#ifdef DOTOUT
	regex_dotout(regex, __PRETTY_FUNCTION__);
	#endif
	
	EXIT;
	return (struct rbundle) {
		.is_nfa = false,
		.dfa = regex,
	};
}
