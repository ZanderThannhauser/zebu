

#include <string.h>
#include <assert.h>
#include <debug.h>

#include <lex/lookup/add_token.h>

/*#include <memory/arena/malloc.h>*/

#include <lex/regex/from_literal.h>
#include <lex/regex/from_charset.h>
#include <lex/regex/clone.h>
#include <lex/regex/dotout.h>
#include <lex/regex/state/add_lambda_transition.h>
#include <lex/regex/nfa_to_dfa/nfa_to_dfa.h>
#include <lex/regex/dfa_to_nfa.h>
#include <lex/regex/simplify_dfa/simplify_dfa.h>
#include <lex/regex/state/struct.h>
#include <lex/regex/state/free.h>
/*#include "../token/root.h"*/

#include <yacc/gegex/from_token.h>
/*#include "gegex/from_empty.h"*/
#include <yacc/gegex/from_subgrammar.h>
#include <yacc/gegex/dotout.h>
#include <yacc/gegex/clone.h>
#include <yacc/gegex/dfa_to_nfa.h>

#include "../charset/root.h"

#include "../options/struct.h"

/*#include "../scope/struct.h"*/
#include "../scope/lookup/inline_grammar.h"
#include "../scope/build_absolute_name.h"
/*#include "../scope/translate/grammar.h"*/
/*#include "../scope/pop.h"*/

/*#include "../read_charset.h"*/
/*#include "../read_fragment.h"*/
/*#include "../read_grammar.h"*/

#include "../token/rbundle.h"
#include "../token/root.h"

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"

/*#include "../tokenizer/machines/subroot.h"*/
#include "../tokenizer/machines/production/root.h"
#include "../tokenizer/machines/production/after_highest.h"
#include "../tokenizer/machines/regex/root.h"
#include "../tokenizer/machines/charset/root.h"

#include "root.h"
#include "highest.h"

struct gbundle read_highest_production(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct options* options,
	struct scope* scope,
	struct lex* lex)
{
	struct gbundle retval;
	ENTER;
	
	TODO;
	#if 0
	switch (tokenizer->token)
	{
		case t_oparen:
		{
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ production_root_machine);
			
			retval = read_root_production(tokenizer, scratchpad, options, scope, lex);
			
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
			
			if (options->skip)
			{
				struct rbundle nfa = regex_dfa_to_nfa(start, scratchpad);
				
				struct regex* clone = regex_clone(options->skip, scratchpad);
				
				regex_add_lambda_transition(clone, scratchpad, start);
				
				#ifdef DEBUGGING
				regex_dotout(clone, __PRETTY_FUNCTION__);
				#endif
				
				nfa.nfa.end->is_accepting = true;
				
				struct regex* dfa = regex_nfa_to_dfa(clone, scratchpad);
				
				start = regex_simplify_dfa(dfa, scratchpad);
				
				free_regex(clone, scratchpad), free_regex(dfa, scratchpad);
				
				#ifdef DEBUGGING
				regex_dotout(start, __PRETTY_FUNCTION__);
				#endif
			}
			
			unsigned token_id = lex_add_token(lex, start, /* is_literal: */ true);
			
			dpv(token_id);
			
			retval = gegex_from_token(
				/* scratchpad: */ scratchpad,
				/* token_id: */ token_id);
			
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ production_after_highest_machine);
			
			#ifdef DEBUGGING
			gegex_dotout(retval.start, retval.end, __PRETTY_FUNCTION__);
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
			
			if (options->skip)
			{
				struct rbundle nfa = regex_dfa_to_nfa(start, scratchpad);
				
				struct regex* clone = regex_clone(options->skip, scratchpad);
				
				regex_add_lambda_transition(clone, scratchpad, start);
				
				#ifdef DEBUGGING
				regex_dotout(clone, __PRETTY_FUNCTION__);
				#endif
				
				nfa.nfa.end->is_accepting = true;
				
				struct regex* dfa = regex_nfa_to_dfa(clone, scratchpad);
				
				start = regex_simplify_dfa(dfa, scratchpad);
				
				free_regex(clone, scratchpad), free_regex(dfa, scratchpad);
				
				#ifdef DEBUGGING
				regex_dotout(start, __PRETTY_FUNCTION__);
				#endif
			}
			
			unsigned token_id = lex_add_token(lex, start, /* is_literal: */ true);
			
			dpv(token_id);
			
			retval = gegex_from_token(
				/* scratchpad: */ scratchpad,
				/* token_id: */ token_id);
			
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ production_after_highest_machine);
			
			#ifdef DEBUGGING
			gegex_dotout(retval.start, retval.end, __PRETTY_FUNCTION__);
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
			
			if (options->skip)
			{
				struct rbundle nfa = regex_dfa_to_nfa(start, scratchpad);
				
				struct regex* clone = regex_clone(options->skip, scratchpad);
				
				regex_add_lambda_transition(clone, scratchpad, start);
				
				#ifdef DEBUGGING
				regex_dotout(clone, __PRETTY_FUNCTION__);
				#endif
				
				nfa.nfa.end->is_accepting = true;
				
				struct regex* dfa = regex_nfa_to_dfa(clone, scratchpad);
				
				start = regex_simplify_dfa(dfa, scratchpad);
				
				free_regex(clone, scratchpad), free_regex(dfa, scratchpad);
				
				#ifdef DEBUGGING
				regex_dotout(start, __PRETTY_FUNCTION__);
				#endif
			}
			
			unsigned token_id = lex_add_token(lex, start, false);
			
			dpv(token_id);
			
			retval = gegex_from_token(
				/* scratchpad: */ scratchpad,
				/* token_id: */ token_id);
			
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ production_after_highest_machine);
			#ifdef DEBUGGING
			gegex_dotout(retval.start, retval.end, __PRETTY_FUNCTION__);
			#endif
			break;
		}
		
		case t_gravemark:
		{
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ regex_root_machine);
			
			struct rbundle regex = read_root_token_expression(tokenizer, scratchpad, scope, options->token_skip);
			
			if (tokenizer->token != t_gravemark)
			{
				TODO;
				exit(1);
			}
			
			struct regex* start;
			
			if (options->skip)
			{
				if (!regex.is_nfa)
					regex = regex_dfa_to_nfa(regex.dfa, scratchpad);
				
				struct regex* clone = regex_clone(options->skip, scratchpad);
				
				regex_add_lambda_transition(clone, scratchpad, regex.nfa.start);
				
				regex.nfa.start = clone;
				
				#ifdef DEBUGGING
				regex_dotout(regex.nfa.start, __PRETTY_FUNCTION__);
				#endif
			}
			
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
			
			unsigned token_id = lex_add_token(lex, start, regex.is_literal);
			
			dpv(token_id);
			
			retval = gegex_from_token(
				/* scratchpad: */ scratchpad,
				/* token_id: */ token_id);
			
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ production_after_highest_machine);
			
			#ifdef DEBUGGING
			gegex_dotout(retval.start, retval.end, __PRETTY_FUNCTION__);
			#endif
			break;
		}
		
		case t_identifier:
		{
			dpvs(tokenizer->tokenchars.chars);
			
			struct gbundle inlined;
			
			if ((inlined = scope_lookup_inline_grammar(scope, tokenizer->tokenchars.chars)).start)
			{
				retval = gegex_clone_nfa(scratchpad, inlined.start, inlined.end);
			}
			else
			{
				char* full_name = scope_build_absolute_name(scope, scratchpad, tokenizer->tokenchars.chars, tokenizer->tokenchars.n);
				
				retval = gegex_from_subgrammar(
					/* grammar name: */ full_name,
					/* scratchpad: */ scratchpad);
			}
			
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ production_after_highest_machine);
			
			#ifdef DEBUGGING
			gegex_dotout(retval.start, retval.end, __PRETTY_FUNCTION__);
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
	#endif
}













