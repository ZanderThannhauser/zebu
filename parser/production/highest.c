
#include <debug.h>

#include <lex/get_token_id.h>

#include <memory/arena/malloc.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"

#include "../tokenizer/machines/subroot.h"
#include "../tokenizer/machines/production/root.h"
#include "../tokenizer/machines/production/after_highest.h"
#include "../tokenizer/machines/expression/root.h"

#include "../token/regex/from_literal.h"
#include "../token/regex/nfa_to_dfa/nfa_to_dfa.h"
#include "../token/regex/simplify_dfa/simplify_dfa.h"
#include "../token/regex/state/free.h"
#include "../token/root.h"

#include "../scope/struct.h"
/*#include "../scope/push.h"*/
/*#include "../scope/translate/grammar.h"*/
/*#include "../scope/pop.h"*/

/*#include "../read_charset.h"*/
/*#include "../read_fragment.h"*/
/*#include "../read_grammar.h"*/

#include "gegex/from_token.h"
#include "gegex/from_empty.h"
#include "gegex/from_subgrammar.h"

#include "root.h"
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
		{
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ production_root_machine);
			
			retval = read_root_production(tokenizer, scratchpad, scope, lex);
			
			if (tokenizer->token != t_cparen)
			{
				TODO;
				exit(1);
			}
			
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ production_after_highest_machine);
			break;
		}
		
		case t_character_literal:
		{
			dpvc(tokenizer->tokenchars.chars[1]);
			
			struct regex* start = regex_from_literal(
				/* scratchpad: */ scratchpad,
				/* chars:      */ tokenizer->tokenchars.chars + 1,
				/* strlen:     */ 1);
			
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
		{
			dpvs(tokenizer->tokenchars.chars);
			
			dpvsn(scope->prefix.chars, scope->prefix.n);
			
			char* full = arena_malloc(
				scratchpad,
				scope->prefix.n + 1 + 
				tokenizer->tokenchars.n + 1), *m = full;
			
			memcpy(m, scope->prefix.chars, scope->prefix.n);
			m += scope->prefix.n;
			*m++ = '.';
			
			memcpy(m, tokenizer->tokenchars.chars, tokenizer->tokenchars.n);
			m += tokenizer->tokenchars.n;
			*m++ = '\0';
			
			dpvs(full);
			
			retval = gegex_from_subgrammar(
				/* grammar name: */ full,
				/* scratchpad: */ scratchpad);
			
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ production_after_highest_machine);
			break;
		}
		
		case t_vertical_bar:
		case t_ampersand:
		case t_cparen:
		{
			retval = gegex_from_empty(
				/* scratchpad: */ scratchpad);
			break;
		}
		
		default:
			TODO;
			break;
	}
	
		
	EXIT;
	return retval;
}













