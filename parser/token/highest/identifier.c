
#include <debug.h>

#include <parser/tokenizer/struct.h>

#include <parser/scope/lookup/fragment.h>

#include <lex/regex/clone.h>
#include <lex/regex/dotout.h>

#include "identifier.h"

struct rbundle read_identifier_token_expression(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct regex* token_skip
) {
	ENTER;
	
	dpvs(tokenizer->tokenchars.chars);
	
	struct regex* original = scope_lookup_fragment(scope, (void*) tokenizer->tokenchars.chars);
	
	struct regex* start = regex_clone(original);
	
	#ifdef DOTOUT
	regex_dotout(start, __PRETTY_FUNCTION__);
	#endif
	
	EXIT;
	return (struct rbundle) {
		.is_nfa = false,
		.dfa = start,
	};
}
