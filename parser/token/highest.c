
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"

#include "../tokenizer/machines/charset/root.h"
#include "../tokenizer/machines/expression/root.h"
#include "../tokenizer/machines/expression/after_highest.h"

#include "../scope/lookup/token.h"

#include "../charset/root.h"

#include <lex/regex/dotout.h>
#include <lex/regex/clone.h>
#include <lex/regex/from_dot.h>
#include <lex/regex/from_charset.h>
#include <lex/regex/from_literal.h>

#include "root.h"
#include "highest.h"

struct rbundle read_highest_token_expression(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct scope* scope)
{
	struct rbundle retval;
	ENTER;
	
	switch (tokenizer->token)
	{
		case t_character_literal:
		{
			dpvc(tokenizer->tokenchars.chars[0]);
			
			struct regex* dfa = regex_from_literal(
				/* scratchpad: */ scratchpad,
				/* chars:      */ tokenizer->tokenchars.chars,
				/* strlen:     */ 1);
			
			retval = (struct rbundle) {
				.is_nfa = false,
				.dfa = dfa,
			};
			
			#ifdef DEBUGGING
			regex_dotout(retval.dfa);
			#endif
			break;
		}
		
		case t_string_literal:
		{
			dpvsn(tokenizer->tokenchars.chars, tokenizer->tokenchars.n);
			
			struct regex* dfa = regex_from_literal(
				/* scratchpad: */ scratchpad,
				/* chars:      */ tokenizer->tokenchars.chars,
				/* strlen:     */ tokenizer->tokenchars.n);
			
			retval = (struct rbundle) {
				.is_nfa = false,
				.dfa = dfa,
			};
			
			#ifdef DEBUGGING
			regex_dotout(retval.dfa);
			#endif
			break;
		}
		
		case t_identifier:
		{
			dpvs(tokenizer->tokenchars.chars);
			
			struct regex* original = scope_lookup_token(scope, tokenizer->tokenchars.chars);
			
			struct regex* start = regex_clone(scratchpad, original);
			
			retval = (struct rbundle) {
				.is_nfa = false,
				.dfa = start,
			};
			
			#ifdef DEBUGGING
			regex_dotout(retval.dfa);
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
			
			retval = (struct rbundle) {
				.is_nfa = false,
				.dfa = regex_from_charset(charset, scratchpad),
			};
			
			#ifdef DEBUGGING
			regex_dotout(retval.dfa);
			#endif
			break;
		}
		
		case t_oparen:
		{
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ expression_root_machine);
			
			retval = read_root_token_expression(tokenizer, scratchpad, scope);
			
			if (tokenizer->token != t_cparen)
			{
				TODO;
				exit(1);
			}
			break;
		}
		
		case t_dot:
		{
			retval = (struct rbundle) {
				.is_nfa = false,
				.dfa = regex_from_dot(scratchpad),
			};
			
			#ifdef DEBUGGING
			regex_dotout(retval.dfa);
			#endif
			break;
		}
		
		default:
			TODO;
			break;
	}
	
	read_token(
		/* tokenizer: */ tokenizer,
		/* machine:   */ expression_after_highest_machine);
	
	EXIT;
	return retval;
}


















