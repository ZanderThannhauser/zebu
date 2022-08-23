
#include <assert.h>

#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/subroot.h"
#include "../tokenizer/machines/production/inside_subdefinitions.h"

#include "../options/struct.h"

#include "../scope/push.h"
#include "../scope/pop.h"

#include "../read_charset.h"
#include "../read_fragment.h"
#include "../read_inline_grammar.h"
#include "../read_grammar.h"

#include "suffixes.h"
#include "subdefinitions.h"

struct gbundle read_subdefinitions_production(
	#ifdef WITH_ARENAS
	struct memory_arena* grammar_arena,
	struct memory_arena* token_arena,
	#endif
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct lex* lex)
{
	struct gbundle retval;
	ENTER;
	
	if (tokenizer->token == t_percent)
	{
		read_token(tokenizer, subroot_machine);
		
		scope_push(scope);
		
		while (tokenizer->token != t_colon)
		{
			switch (tokenizer->token)
			{
				case t_bracketed_identifier:
				{
					read_charset(tokenizer, scope);
					break;
				}
				
				case t_gravemarked_identifier:
				{
					read_fragment(tokenizer, scope, options->token_skip);
					break;
				}
				
				case t_parenthesised_identifier:
				{
					#ifdef WITH_ARENAS
					read_inline_grammar(token_arena, tokenizer, options, scope, lex);
					#else
					read_inline_grammar(tokenizer, options, scope, lex);
					#endif
					break;
				}
				
				case t_identifier:
				{
					#ifdef WITH_ARENAS
					read_grammar(grammar_arena, token_arena, tokenizer, options, scope, lex);
					#else
					read_grammar(tokenizer, options, scope, lex);
					#endif
					break;
				}
				
				default:
					TODO;
					break;
			}
			
			if (tokenizer->token == t_semicolon)
			{
				read_token(tokenizer, subroot_machine);
			}
		}
		
		// read production rule:
		read_token(tokenizer, production_inside_subdefinitions_machine);
		
		#ifdef WITH_ARENAS
		retval = read_suffixes_production(grammar_arena, token_arena, tokenizer, options, scope, lex);
		#else
		retval = read_suffixes_production(tokenizer, options, scope, lex);
		#endif
		
		scope_pop(scope);
	}
	else
	{
		#ifdef WITH_ARENAS
		retval = read_suffixes_production(grammar_arena, token_arena, tokenizer, options, scope, lex);
		#else
		retval = read_suffixes_production(tokenizer, options, scope, lex);
		#endif
	}
	
	EXIT;
	return retval;
}















