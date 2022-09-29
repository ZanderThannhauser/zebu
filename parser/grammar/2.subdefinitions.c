
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <enums/error.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/token_names.h"
#include "../tokenizer/read_token.h"

/*#include "../options/struct.h"*/

#include "../scope/push.h"
#include "../scope/pop.h"

#include "../read_charset.h"
#include "../read_fragment.h"
#include "../read_inline_grammar.h"
#include "../read_grammar.h"

#include "1.suffixes.h"
#include "2.subdefinitions.h"

struct gbundle read_subdefinitions_production(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex)
{
	struct gbundle retval;
	ENTER;
	
	if (tokenizer->token == t_percent)
	{
		read_token(tokenizer);
		
		scope_push(scope);
		
		while (tokenizer->token != t_colon)
		{
			switch (tokenizer->token)
			{
				case t_osquare:
					read_charset(tokenizer, scope);
					break;
				
				case t_gravemark:
					read_fragment(tokenizer, scope);
					break;
				
				case t_oparen:
					read_inline_grammar(tokenizer, scope, lex);
					break;
				
				case t_identifier:
					read_grammar(tokenizer, scope, lex);
					break;
				
				default:
					TODO;
					break;
			}
			
			if (tokenizer->token != t_semicolon && tokenizer->token != t_colon)
			{
				fprintf(stderr, "zebu: encountered syntax error on line %u: "
					"unexpected '%s', expecting either '%s' or '%s'!\n",
					tokenizer->line,
					token_names[tokenizer->token],
					token_names[t_semicolon],
					token_names[t_colon]);
				exit(e_syntax_error);
			}
			
			if (tokenizer->token == t_semicolon)
				read_token(tokenizer);
		}
		
		read_token(tokenizer);
		
		retval = read_suffixes_production(tokenizer, scope, lex);
		
		scope_pop(scope);
	}
	else
	{
		retval = read_suffixes_production(tokenizer, scope, lex);
	}
	
	EXIT;
	return retval;
}














