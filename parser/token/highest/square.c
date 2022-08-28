
#include <debug.h>

#include <parser/charset/root.h>

#include <parser/tokenizer/struct.h>
#include <parser/tokenizer/read_token.h>
#include <parser/tokenizer/machines/charset/root.h>

#include <lex/regex/from_charset.h>
#include <lex/regex/dotout.h>

#include "square.h"

struct rbundle read_square_token_expression(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct regex* token_skip
) {
	ENTER;
	
	read_token(tokenizer, charset_root_machine);
	
	struct charset* charset = read_root_charset(tokenizer, scope);
	
	dpv(charset);
	
	if (tokenizer->token != t_csquare)
	{
		TODO;
		exit(1);
	}
	
	struct regex* dfa = regex_from_charset(charset);
	
	#ifdef DOTOUT
	regex_dotout(dfa, __PRETTY_FUNCTION__);
	#endif
	
	EXIT;
	return (struct rbundle) {
		.is_nfa = false,
		.dfa = dfa,
	};
}




