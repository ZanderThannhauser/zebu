
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include <debug.h>

#include <string/new.h>
#include <string/free.h>

#include <enums/error.h>

#include "charset/root.h"

#include "tokenizer/struct.h"
#include "tokenizer/token_names.h"
#include "tokenizer/read_token.h"

#include "scope/declare/charset.h"

#include "read_charset.h"

void read_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	assert(tokenizer->token == t_osquare);
	
	read_token(tokenizer);
	
	if (tokenizer->token != t_identifier)
	{
		fprintf(stderr, "zebu: encountered syntax error on line %u: "
			"unexpected '%s', expecting '%s'!\n",
			tokenizer->line,
			token_names[tokenizer->token],
			token_names[t_identifier]);
		exit(e_syntax_error);
	}
	
	struct string* name = new_string_from_tokenchars(tokenizer);
	
	read_token(tokenizer);
	
	if (tokenizer->token != t_csquare)
	{
		fprintf(stderr, "zebu: encountered syntax error on line %u: "
			"unexpected '%s', expecting '%s'!\n",
			tokenizer->line,
			token_names[tokenizer->token],
			token_names[t_csquare]);
		exit(e_syntax_error);
	}
	
	read_token(tokenizer);
		
	if (tokenizer->token != t_colon)
	{
		fprintf(stderr, "zebu: encountered syntax error on line %u: "
			"unexpected '%s', expecting '%s'!\n",
			tokenizer->line,
			token_names[tokenizer->token],
			token_names[t_colon]);
		exit(e_syntax_error);
	}
	
	read_token(tokenizer);
	
	charset_t charset = read_root_charset(tokenizer, scope);
	
	scope_declare_charset(scope, name, charset);
	
	free_string(name);
	
	EXIT;
}



















