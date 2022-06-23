
#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"

#include "../tokenizer/machines/charset/root.h"
#include "../tokenizer/machines/expression/root.h"
#include "../tokenizer/machines/expression/after_highest.h"

#include "../scope/lookup/token.h"

#include "../charset/root.h"

#include "regex/clone.h"
#include "regex/from_dot.h"
#include "regex/from_charset.h"
#include "regex/from_literal.h"

#include "root.h"
#include "highest.h"

struct bundle read_highest_token_expression(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct scope* scope)
{
	struct bundle retval;
	ENTER;
	
	switch (tokenizer->token)
	{
		case t_string_literal:
		{
			dpvsn(tokenizer->tokenchars.chars, tokenizer->tokenchars.n);
			
			dpvsn(tokenizer->tokenchars.chars + 1, tokenizer->tokenchars.n - 2);
			
			struct regex* start = regex_from_literal(
				/* scratchpad: */ scratchpad,
				/* chars:      */ tokenizer->tokenchars.chars + 1,
				/* strlen:     */ tokenizer->tokenchars.n - 2);
			
			retval = (struct bundle) {
				.regex = start,
				.is_nfa = false,
			};
			
			break;
		}
		
		case t_identifier:
		{
			dpvs(tokenizer->tokenchars.chars);
			
			struct regex* original = scope_lookup_token(scope, tokenizer->tokenchars.chars);
			
			struct regex* start = regex_clone(scratchpad, original);
			
			retval = (struct bundle) {
				.regex = start,
				.is_nfa = false,
			};
			
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
			
			retval = (struct bundle) {
				.regex = regex_from_charset(charset, scratchpad),
				.is_nfa = false,
			};
			
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
			retval = (struct bundle) {
				.regex = regex_from_dot(scratchpad),
				.is_nfa = false,
			};
			
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









