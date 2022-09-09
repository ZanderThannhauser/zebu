
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <parser/charset/root.h>

#include <parser/tokenizer/struct.h>
#include <parser/tokenizer/read_token.h>
#include <parser/tokenizer/machines/charset/root.h>

#include <regex/from_charset.h>
#include <regex/dotout.h>

#include "square.h"

struct rbundle read_square_token_expression(
	struct tokenizer* tokenizer,
	struct scope* scope
) {
	ENTER;
	
	read_token(tokenizer, charset_root_machine);
	
	charset_t charset = read_root_charset(tokenizer, scope);
	
	if (tokenizer->token != t_csquare)
	{
		TODO;
		exit(1);
	}
	
	struct regex* start = regex_from_charset(charset);
	
	EXIT;
	return (struct rbundle) {
		.is_nfa = false,
		.dfa = start,
	};
}



















