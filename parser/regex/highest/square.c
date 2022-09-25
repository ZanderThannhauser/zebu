
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <enums/error.h>

#include <parser/charset/root.h>

#include <parser/tokenizer/struct.h>
#include <parser/tokenizer/read_token.h>
#include <parser/tokenizer/token_names.h>

#include <regex/from_charset.h>
#include <regex/dotout.h>

#include "square.h"

struct rbundle read_square_token_expression(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	assert(tokenizer->token == t_osquare);
	
	read_token(tokenizer);
	
	charset_t charset = read_root_charset(tokenizer, scope);
	
	if (tokenizer->token != t_csquare)
	{
		assert(token_names[tokenizer->token]);
		assert(token_names[t_csquare]);
		
		fprintf(stderr, "zebu: error while reading end of character set: "
			"unexpected '%s' token on line %u, expecting '%s'!\n",
			token_names[tokenizer->token],
			tokenizer->line,
			token_names[t_csquare]);
		
		exit(e_syntax_error);
	}
	
	struct regex* start = regex_from_charset(charset);
	
	EXIT;
	return (struct rbundle){start, NULL};
}



















