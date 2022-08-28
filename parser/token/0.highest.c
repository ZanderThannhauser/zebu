
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"

/*#include "../tokenizer/machines/charset/root.h"*/
/*#include "../tokenizer/machines/regex/root.h"*/
#include "../tokenizer/machines/regex/after_highest.h"

/*#include "../scope/lookup/token.h"*/

/*#include "../charset/root.h"*/

/*#include <lex/regex/dotout.h>*/
/*#include <lex/regex/clone.h>*/
/*#include <lex/regex/from_dot.h>*/
/*#include <lex/regex/from_charset.h>*/
/*#include <lex/regex/from_literal.h>*/

#include "highest/character_literal.h"
#include "highest/string_literal.h"
#include "highest/square.h"

/*#include "root.h"*/
#include "0.highest.h"

struct rbundle read_highest_token_expression(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct regex* token_skip
) {
	struct rbundle retval;
	ENTER;
	
	switch (tokenizer->token)
	{
		case t_character_literal:
			retval = read_character_literal_token_expression(tokenizer, scope, token_skip);
			break;
		
		case t_string_literal:
			retval = read_string_literal_token_expression(tokenizer, scope, token_skip);
			break;
		
		case t_identifier:
		{
			TODO;
			#if 0
			dpvs(tokenizer->tokenchars.chars);
			
			struct regex* original = scope_lookup_token(scope, tokenizer->tokenchars.chars);
			
			#ifdef WITH_ARENAS
			struct regex* start = regex_clone(arena, original);
			#else
			struct regex* start = regex_clone(original);
			#endif
			
			retval = (struct rbundle) {
				.is_nfa = false,
				.dfa = start,
			};
			
			#ifdef DOTOUT
			regex_dotout(retval.dfa, __PRETTY_FUNCTION__);
			#endif
			#endif
			break;
		}
		
		case t_osquare:
			retval = read_square_token_expression(tokenizer, scope, token_skip);
			break;
		
		case t_oparen:
		{
			TODO;
			#if 0
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ regex_root_machine);
			
			#ifdef WITH_ARENAS
			retval = read_root_token_expression(arena, tokenizer, scope, token_skip);
			#else
			retval = read_root_token_expression(tokenizer, scope, token_skip);
			#endif
			
			if (tokenizer->token != t_cparen)
			{
				TODO;
				exit(1);
			}
			
			#endif
			break;
		}
		
		case t_dot:
		{
			TODO;
			#if 0
			retval = (struct rbundle) {
				.is_nfa = false,
				#ifdef WITH_ARENAS
				.dfa = regex_from_dot(arena),
				#else
				.dfa = regex_from_dot(),
				#endif
			};
			
			#ifdef DOTOUT
			regex_dotout(retval.dfa, __PRETTY_FUNCTION__);
			#endif
			#endif
			break;
		}
		
		default:
			TODO;
			break;
	}
	
	read_token(
		/* tokenizer: */ tokenizer,
		/* machine:   */ regex_after_highest_machine);
	
	EXIT;
	return retval;
}

















