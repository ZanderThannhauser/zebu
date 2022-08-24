
#include <stdlib.h>
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

#include "../charset/charset/free.h"
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
	
	switch (tokenizer->token)
	{
		case t_oparen:
		{
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ production_root_machine);
			
			#ifdef WITH_ARENAS
			retval = read_root_production(grammar_arena, token_arena, tokenizer, options, scope, lex);
			#else
			retval = read_root_production(tokenizer, options, scope, lex);
			#endif
			
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
				#ifdef WITH_ARENAS
				/* scratchpad: */ token_arena,
				#endif
				/* chars:      */ tokenizer->tokenchars.chars,
				/* strlen:     */ 1);
			
			if (options->skip)
			{
				#ifdef WITH_ARENAS
				struct rbundle nfa = regex_dfa_to_nfa(token_arena, start);
				struct regex* clone = regex_clone(token_arena, options->skip);
				#else
				struct rbundle nfa = regex_dfa_to_nfa(start);
				struct regex* clone = regex_clone(options->skip);
				#endif
				
				regex_add_lambda_transition(clone, start);
				
				#ifdef DOTOUT
				regex_dotout(clone, __PRETTY_FUNCTION__);
				#endif
				
				nfa.nfa.end->is_accepting = true;
				
				#ifdef WITH_ARENAS
				struct regex* dfa = regex_nfa_to_dfa(token_arena, clone);
				start = regex_simplify_dfa(token_arena, dfa);
				#else
				struct regex* dfa = regex_nfa_to_dfa(clone);
				start = regex_simplify_dfa(dfa);
				#endif
				
				#ifdef DOTOUT
				regex_dotout(start, __PRETTY_FUNCTION__);
				#endif
				
				free_regex(clone), free_regex(dfa);
			}
			
			unsigned token_id = lex_add_token(lex, start, /* is_literal: */ true);
			
			dpv(token_id);
			
			retval = gegex_from_token(
				#ifdef WITH_ARENAS
				/* scratchpad: */ grammar_arena,
				#endif
				/* token_id: */ token_id);
			
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ production_after_highest_machine);
			
			#ifdef DOTOUT
			gegex_dotout(retval.start, retval.end, __PRETTY_FUNCTION__);
			#endif
			break;
		}
		
		case t_string_literal:
		{
			dpvsn(tokenizer->tokenchars.chars, tokenizer->tokenchars.n);
			
			struct regex* start = regex_from_literal(
				#ifdef WITH_ARENAS
				/* arena:  */ token_arena,
				#endif
				/* chars:  */ tokenizer->tokenchars.chars,
				/* strlen: */ tokenizer->tokenchars.n);
			
			if (options->skip)
			{
				#ifdef WITH_ARENAS
				struct rbundle nfa = regex_dfa_to_nfa(token_arena, start);
				struct regex* clone = regex_clone(token_arena, options->skip);
				#else
				struct rbundle nfa = regex_dfa_to_nfa(start);
				struct regex* clone = regex_clone(options->skip);
				#endif
				
				regex_add_lambda_transition(clone, start);
				
				#ifdef DOTOUT
				regex_dotout(clone, __PRETTY_FUNCTION__);
				#endif
				
				nfa.nfa.end->is_accepting = true;
				
				#ifdef WITH_ARENAS
				struct regex* dfa = regex_nfa_to_dfa(token_arena, clone);
				start = regex_simplify_dfa(token_arena, dfa);
				#else
				struct regex* dfa = regex_nfa_to_dfa(clone);
				start = regex_simplify_dfa(dfa);
				#endif
				
				#ifdef DOTOUT
				regex_dotout(start, __PRETTY_FUNCTION__);
				#endif
				
				free_regex(clone), free_regex(dfa);
			}
			
			unsigned token_id = lex_add_token(lex, start, /* is_literal: */ true);
			
			dpv(token_id);
			
			retval = gegex_from_token(
				#ifdef WITH_ARENAS
				/* scratchpad: */ grammar_arena,
				#endif
				/* token_id: */ token_id);
			
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ production_after_highest_machine);
			
			#ifdef DOTOUT
			gegex_dotout(retval.start, retval.end, __PRETTY_FUNCTION__);
			#endif
			break;
		}
		
		case t_osquare:
		{
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ charset_root_machine);
			
			#ifdef WITH_ARENAS
			struct charset* charset = read_root_charset(token_arena, tokenizer, scope);
			#else
			struct charset* charset = read_root_charset(tokenizer, scope);
			#endif
			
			dpv(charset);
			
			if (tokenizer->token != t_csquare)
			{
				TODO;
				exit(1);
			}
			
			#ifdef WITH_ARENAS
			struct regex* start = regex_from_charset(token_arena, charset);
			#else
			struct regex* start = regex_from_charset(charset);
			#endif
			
			if (options->skip)
			{
				#ifdef WITH_ARENAS
				struct rbundle nfa = regex_dfa_to_nfa(token_arena, start);
				struct regex* clone = regex_clone(token_arena, options->skip);
				#else
				struct rbundle nfa = regex_dfa_to_nfa(start);
				struct regex* clone = regex_clone(options->skip);
				#endif
				
				regex_add_lambda_transition(clone, start);
				
				#ifdef DOTOUT
				regex_dotout(clone, __PRETTY_FUNCTION__);
				#endif
				
				nfa.nfa.end->is_accepting = true;
				
				#ifdef WITH_ARENAS
				struct regex* dfa = regex_nfa_to_dfa(token_arena, clone);
				start = regex_simplify_dfa(token_arena, dfa);
				#else
				struct regex* dfa = regex_nfa_to_dfa(clone);
				start = regex_simplify_dfa(dfa);
				#endif
				
				#ifdef DOTOUT
				regex_dotout(start, __PRETTY_FUNCTION__);
				#endif
				
				free_regex(clone), free_regex(dfa);
			}
			
			unsigned token_id = lex_add_token(lex, start, false);
			
			dpv(token_id);
			
			retval = gegex_from_token(
				#ifdef WITH_ARENAS
				/* scratchpad: */ grammar_arena,
				#endif
				/* token_id: */ token_id);
			
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ production_after_highest_machine);
			
			#ifdef DOTOUT
			gegex_dotout(retval.start, retval.end, __PRETTY_FUNCTION__);
			#endif
			
			free_charset(charset);
			break;
		}
		
		case t_gravemark:
		{
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ regex_root_machine);
			
			#ifdef WITH_ARENAS
			struct rbundle regex = read_root_token_expression(token_arena, tokenizer, scope, options->token_skip);
			#else
			struct rbundle regex = read_root_token_expression(tokenizer, scope, options->token_skip);
			#endif
			
			if (tokenizer->token != t_gravemark)
			{
				TODO;
				exit(1);
			}
			
			struct regex* start;
			
			if (options->skip)
			{
				if (!regex.is_nfa)
				{
					#ifdef WITH_ARENAS
					regex = regex_dfa_to_nfa(token_arena, regex.dfa);
					#else
					regex = regex_dfa_to_nfa(regex.dfa);
					#endif
				}
				
				#ifdef WITH_ARENAS
				struct regex* clone = regex_clone(token_arena, options->skip);
				#else
				struct regex* clone = regex_clone(options->skip);
				#endif
				
				regex_add_lambda_transition(clone, regex.nfa.start);
				
				regex.nfa.start = clone;
				
				#ifdef DOTOUT
				regex_dotout(regex.nfa.start, __PRETTY_FUNCTION__);
				#endif
			}
			
			if (regex.is_nfa)
			{
				regex.nfa.end->is_accepting = true;
				
				struct regex* nfa = regex.nfa.start;
				
				#ifdef WITH_ARENAS
				struct regex* dfa = regex_nfa_to_dfa(token_arena, nfa);
				start = regex_simplify_dfa(token_arena, dfa);
				#else
				struct regex* dfa = regex_nfa_to_dfa(nfa);
				start = regex_simplify_dfa(dfa);
				#endif
				
				
				free_regex(nfa), free_regex(dfa);
			}
			else
			{
				start = regex.dfa;
			}
			
			unsigned token_id = lex_add_token(lex, start, regex.is_literal);
			
			dpv(token_id);
			
			retval = gegex_from_token(
				#ifdef WITH_ARENAS
				/* scratchpad: */ grammar_arena,
				#endif
				/* token_id: */ token_id);
			
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ production_after_highest_machine);
			
			#ifdef DOTOUT
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
				#ifdef WITH_ARENAS
				retval = gegex_clone_nfa(grammar_arena, inlined.start, inlined.end);
				#else
				retval = gegex_clone_nfa(inlined.start, inlined.end);
				#endif
			}
			else
			{
				#ifdef WITH_ARENAS
				char* full_name = scope_build_absolute_name(scope, grammar_arena, tokenizer->tokenchars.chars, tokenizer->tokenchars.n);
				#else
				char* full_name = scope_build_absolute_name(scope, tokenizer->tokenchars.chars, tokenizer->tokenchars.n);
				#endif
				
				retval = gegex_from_subgrammar(
					#ifdef WITH_ARENAS
					/* scratchpad: */ grammar_arena,
					#endif
					/* grammar name: */ full_name);
			}
			
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ production_after_highest_machine);
			
			#ifdef DOTOUT
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
}













