
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"

#include "../tokenizer/machines/charset/root.h"
#include "../tokenizer/machines/regex/root.h"
#include "../tokenizer/machines/regex/after_highest.h"

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
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct regex* token_skip)
{
	struct rbundle retval;
	ENTER;
	
	switch (tokenizer->token)
	{
		case t_character_literal:
		{
			dpvc(tokenizer->tokenchars.chars[0]);
			
			struct regex* dfa = regex_from_literal(
				#ifdef WITH_ARENAS
				/* arena:  */ arena,
				#endif
				/* chars:  */ tokenizer->tokenchars.chars,
				/* strlen: */ 1);
			
			retval = (struct rbundle) {
				.is_literal = true,
				.is_nfa = false,
				.dfa = dfa,
			};
			
			#ifdef DEBUGGING
			regex_dotout(retval.dfa, __PRETTY_FUNCTION__);
			#endif
			break;
		}
		
		case t_string_literal:
		{
			dpvsn(tokenizer->tokenchars.chars, tokenizer->tokenchars.n);
			
			struct regex* dfa = regex_from_literal(
				#ifdef WITH_ARENAS
				/* arena: */ arena,
				#endif
				/* chars:      */ tokenizer->tokenchars.chars,
				/* strlen:     */ tokenizer->tokenchars.n);
			
			retval = (struct rbundle) {
				.is_literal = true,
				.is_nfa = false,
				.dfa = dfa,
			};
			
			#ifdef DEBUGGING
			regex_dotout(retval.dfa, __PRETTY_FUNCTION__);
			#endif
			break;
		}
		
		case t_identifier:
		{
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
			
			#ifdef DEBUGGING
			regex_dotout(retval.dfa, __PRETTY_FUNCTION__);
			#endif
			break;
		}
		
		case t_osquare:
		{
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ charset_root_machine);
			
			#ifdef WITH_ARENAS
			struct charset* charset = read_root_charset(arena, tokenizer, scope);
			#else
			struct charset* charset = read_root_charset(tokenizer, scope);
			#endif
			
			dpv(charset);
			
			if (tokenizer->token != t_csquare)
			{
				TODO;
				exit(1);
			}
			
			retval = (struct rbundle) {
				.is_nfa = false,
				#ifdef WITH_ARENAS
				.dfa = regex_from_charset(arena, charset),
				#else
				.dfa = regex_from_charset(charset),
				#endif
			};
			
			#ifdef DEBUGGING
			regex_dotout(retval.dfa, __PRETTY_FUNCTION__);
			#endif
			break;
		}
		
		case t_oparen:
		{
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
			
			break;
		}
		
		case t_dot:
		{
			retval = (struct rbundle) {
				.is_nfa = false,
				#ifdef WITH_ARENAS
				.dfa = regex_from_dot(arena),
				#else
				.dfa = regex_from_dot(),
				#endif
			};
			
			#ifdef DEBUGGING
			regex_dotout(retval.dfa, __PRETTY_FUNCTION__);
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


















