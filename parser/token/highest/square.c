
#include <debug.h>

#include <parser/charset/root.h>

#include <parser/tokenizer/struct.h>
#include <parser/tokenizer/read_token.h>
#include <parser/tokenizer/machines/charset/root.h>

#include <set/unsignedchar/free.h>

#include <regex/from_charset.h>
#include <regex/dotout.h>

#include "square.h"

struct rbundle read_square_token_expression(
	struct tokenizer* tokenizer,
	struct scope* scope
) {
	ENTER;
	
	read_token(tokenizer, charset_root_machine);
	
	struct cbundle cbundle = read_root_charset(tokenizer, scope);
	
	if (tokenizer->token != t_csquare)
	{
		TODO;
		exit(1);
	}
	
	struct regex* start = regex_from_charset(cbundle.is_complement, cbundle.charset);
	
	free_unsignedcharset(cbundle.charset);
	
	#ifdef DOTOUT
	regex_dotout(start, __PRETTY_FUNCTION__);
	#endif
	
	EXIT;
	return (struct rbundle) {
		.is_nfa = false,
		.dfa = start,
	};
}




