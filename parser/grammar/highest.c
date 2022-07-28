
#include <string.h>
#include <assert.h>
#include <debug.h>

#include <lex/lookup/dfa_to_id.h>

#include <memory/arena/malloc.h>

#include <lex/regex/from_literal.h>
#include <lex/regex/from_charset.h>
#include <lex/regex/nfa_to_dfa/nfa_to_dfa.h>
#include <lex/regex/simplify_dfa/simplify_dfa.h>
#include <lex/regex/state/struct.h>
#include <lex/regex/state/free.h>
/*#include "../token/root.h"*/

#include "../charset/root.h"

#include "../scope/struct.h"
/*#include "../scope/push.h"*/
/*#include "../scope/translate/grammar.h"*/
/*#include "../scope/pop.h"*/

/*#include "../read_charset.h"*/
/*#include "../read_fragment.h"*/
/*#include "../read_grammar.h"*/

#include <yacc/gegex/from_token.h>
/*#include "gegex/from_empty.h"*/
#include <yacc/gegex/from_subgrammar.h>
#include <yacc/gegex/dotout.h>

#include "../token/rbundle.h"
#include "../token/root.h"

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"

/*#include "../tokenizer/machines/subroot.h"*/
#include "../tokenizer/machines/production/root.h"
#include "../tokenizer/machines/production/after_highest.h"
#include "../tokenizer/machines/expression/root.h"
#include "../tokenizer/machines/charset/root.h"

#include "root.h"
#include "highest.h"

struct gbundle read_highest_production(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct scope* scope,
	struct lex* lex)
{
	struct gbundle retval;
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
			dpvc(tokenizer->tokenchars.chars[0]);
			
			struct regex* start = regex_from_literal(
				/* scratchpad: */ scratchpad,
				/* chars:      */ tokenizer->tokenchars.chars,
				/* strlen:     */ 1);
			
			unsigned token_id = lex_dfa_to_id(lex, start);
			
			dpv(token_id);
			
			retval = gegex_from_token(
				/* scratchpad: */ scratchpad,
				/* token_id: */ token_id);
			
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ production_after_highest_machine);
			
			#ifdef DEBUGGING
			gegex_dotout(retval.start, retval.end);
			#endif
			break;
		}
		
		case t_string_literal:
		{
			dpvsn(tokenizer->tokenchars.chars, tokenizer->tokenchars.n);
			
			struct regex* start = regex_from_literal(
				/* scratchpad: */ scratchpad,
				/* chars:      */ tokenizer->tokenchars.chars,
				/* strlen:     */ tokenizer->tokenchars.n);
			
			unsigned token_id = lex_dfa_to_id(lex, start);
			
			dpv(token_id);
			
			retval = gegex_from_token(
				/* scratchpad: */ scratchpad,
				/* token_id: */ token_id);
			
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ production_after_highest_machine);
			#ifdef DEBUGGING
			gegex_dotout(retval.start, retval.end);
			#endif
			break;
		}
		
		case t_osquare:
		{
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ charset_root_machine);
				
			struct charset* charset = read_root_charset(tokenizer, scope);
			
			dpv(charset);
			
			if (tokenizer->token != t_csquare)
			{
				TODO;
				exit(1);
			}
			
			struct regex* start = regex_from_charset(charset, scratchpad);
			
			unsigned token_id = lex_dfa_to_id(lex, start);
			
			dpv(token_id);
			
			retval = gegex_from_token(
				/* scratchpad: */ scratchpad,
				/* token_id: */ token_id);
			
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ production_after_highest_machine);
			#ifdef DEBUGGING
			gegex_dotout(retval.start, retval.end);
			#endif
			break;
		}
		
		case t_gravemark:
		{
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ expression_root_machine);
			
			struct rbundle regex = read_root_token_expression(tokenizer, scratchpad, scope);
			
			if (tokenizer->token != t_gravemark)
			{
				TODO;
				exit(1);
			}
			
			struct regex* start;
			
			if (regex.is_nfa)
			{
				regex.nfa.end->is_accepting = true;
				
				struct regex* nfa = regex.nfa.start;
				struct regex* dfa = regex_nfa_to_dfa(nfa, scratchpad);
				
				start = regex_simplify_dfa(dfa, scratchpad);
				
				free_regex(nfa, scratchpad), free_regex(dfa, scratchpad);
			}
			else
			{
				start = regex.dfa;
			}
			
			unsigned token_id = lex_dfa_to_id(lex, start);
			
			dpv(token_id);
			
			retval = gegex_from_token(
				/* scratchpad: */ scratchpad,
				/* token_id: */ token_id);
			
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ production_after_highest_machine);
			
			#ifdef DEBUGGING
			gegex_dotout(retval.start, retval.end);
			#endif
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
			
			if (scope->prefix.n)
			{
				memcpy(m, scope->prefix.chars, scope->prefix.n);
				m += scope->prefix.n;
				*m++ = '.';
			}
			
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
			
			#ifdef DEBUGGING
			gegex_dotout(retval.start, retval.end);
			#endif
			break;
		}
		
		default:
			TODO;
			break;
	}
	
	dpv(retval.start);
	dpv(retval.end);
	
	EXIT;
	return retval;
}













