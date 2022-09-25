
#include <debug.h>

#include <parser/tokenizer/struct.h>

#include <parser/scope/lookup/fragment.h>

#include <regex/clone.h>
#include <regex/dotout.h>

#include "identifier.h"

struct rbundle read_identifier_token_expression(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	const char* name = (void*) tokenizer->tokenchars.chars;
	
	dpvs(name);
	
	struct regex* original = scope_lookup_fragment(scope, name);
	
	struct rbundle retval = regex_clone2((struct rbundle){original, NULL});
	
	#ifdef DOTOUT
	regex_dotout(retval.start, __PRETTY_FUNCTION__);
	#endif
	
	EXIT;
	return retval;
}















