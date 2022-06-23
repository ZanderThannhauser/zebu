
#include <debug.h>

#include <lex/get_token_id.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"

#include "../tokenizer/machines/production/after_highest.h"
#include "../tokenizer/machines/expression/root.h"

#include "../token/regex/from_literal.h"
#include "../token/regex/nfa_to_dfa/nfa_to_dfa.h"
#include "../token/regex/simplify_dfa/simplify_dfa.h"
#include "../token/regex/state/free.h"
#include "../token/root.h"

#include "gegex/from_token.h"

#include "highest.h"

struct bundle read_highest_production(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct scope* scope,
	struct lex* lex)
{
	struct bundle retval;
	ENTER;
	
	switch (tokenizer->token)
	{
		case t_oparen:
			TODO;
			break;
		
		case t_character_literal:
			TODO;
			break;
		
		case t_string_literal:
		{
			dpvsn(tokenizer->tokenchars.chars, tokenizer->tokenchars.n);
			
			dpvsn(tokenizer->tokenchars.chars + 1, tokenizer->tokenchars.n - 2);
			
			struct regex* start = regex_from_literal(
				/* scratchpad: */ scratchpad,
				/* chars:      */ tokenizer->tokenchars.chars + 1,
				/* strlen:     */ tokenizer->tokenchars.n - 2);
			
			unsigned token_id = lex_get_token_id(lex, start);
			
			dpv(token_id);
			
			retval = gegex_from_token(
				/* scratchpad: */ scratchpad,
				/* token_id: */ token_id);
			
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ production_after_highest_machine);
			break;
		}
		
		case t_gravemark:
		{
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ expression_root_machine);
			
			struct bundle regex = read_root_token_expression(tokenizer, scratchpad, scope);
			
			if (tokenizer->token != t_gravemark)
			{
				TODO;
				exit(1);
			}
			
			struct regex* start;
			
			if (regex.is_nfa)
			{
				struct regex* nfa = regex.regex;
				struct regex* dfa = regex_nfa_to_dfa(nfa, scratchpad);
				
				start = regex_simplify_dfa(dfa, scratchpad);
				
				free_regex(nfa, scratchpad), free_regex(dfa, scratchpad);
			}
			else
			{
				start = regex.regex;
			}
			
			unsigned token_id = lex_get_token_id(lex, start);
			
			dpv(token_id);
			
			retval = gegex_from_token(
				/* scratchpad: */ scratchpad,
				/* token_id: */ token_id);
			
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ production_after_highest_machine);
			break;
		}
		
		case t_identifier:
			TODO;
			break;
		
		default:
			TODO;
			break;
	}
	
	EXIT;
	return retval;
}













