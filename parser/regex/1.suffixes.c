
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <enums/error.h>

#include <regex/dfa_to_nfa.h>
#include <regex/dotout.h>
#include <regex/clone.h>
#include <regex/new.h>
#include <regex/free.h>
#include <regex/add_lambda_transition.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"

#include "0.highest.h"
#include "1.suffixes.h"

struct rbundle read_suffixes_token_expression(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	struct rbundle retval = read_highest_token_expression(tokenizer, scope);
	
	switch (tokenizer->token)
	{
		case t_qmark:
		{
			// convert into nfa:
			if (!retval.is_nfa)
			{
				retval = regex_dfa_to_nfa(retval.dfa);
			}
			
			regex_add_lambda_transition(retval.nfa.start, retval.nfa.accepts);
			
			#ifdef DOTOUT
			regex_dotout(retval.nfa.start, __PRETTY_FUNCTION__);
			#endif
			
			read_token(tokenizer);
			break;
		}
		
		case t_asterisk:
		{
			// convert into nfa:
			if (!retval.is_nfa)
			{
				retval = regex_dfa_to_nfa(retval.dfa);
			}
			
			regex_add_lambda_transition(retval.nfa.accepts, retval.nfa.start);
			regex_add_lambda_transition(retval.nfa.start, retval.nfa.accepts);
			
			#ifdef DOTOUT
			regex_dotout(retval.nfa.start, __PRETTY_FUNCTION__);
			#endif
			
			read_token(tokenizer);
			break;
		}
		
		case t_plus:
		{
			// convert into nfa:
			if (!retval.is_nfa)
			{
				retval = regex_dfa_to_nfa(retval.dfa);
			}
			
			regex_add_lambda_transition(retval.nfa.accepts, retval.nfa.start);
			
			#ifdef DOTOUT
			regex_dotout(retval.nfa.start, __PRETTY_FUNCTION__);
			#endif
			
			read_token(tokenizer);
			break;
		}
		
		case t_ocurly:
		{
			TODO;
			#if 0
			struct rbundle original;
			
			// convert into nfa:
			if (retval.is_nfa)
				original = retval;
			else
				original = regex_dfa_to_nfa(retval.dfa);
			
			struct limit {
				bool has;
				unsigned value;
			} min = {}, max = {};
			
			void set_limit(struct limit* l)
			{
				switch (tokenizer->token)
				{
					case t_octal_literal:
						TODO;
						break;
					
					case t_decimal_literal:
					{
						errno = 0;
						
						const char* start = (void*) tokenizer->tokenchars.chars;
						unsigned long int value = strtoul(start, NULL, 10);
						
						if (errno)
						{
							fprintf(stderr, "zebu: error when reading character-set: strtoul(): %m\n");
							exit(e_syntax_error);
						}
						
						l->has = true;
						l->value = value;
						break;
					}
					
					case t_hexadecimal_literal:
						TODO;
						break;
					
					default:
						TODO;
						break;
				}
			}
			
			read_token(tokenizer, numeric_or_comma_machine);
			
			if (false
				|| tokenizer->token == t_octal_literal
				|| tokenizer->token == t_decimal_literal
				|| tokenizer->token == t_hexadecimal_literal)
			{
				set_limit(&min);
				read_token(tokenizer, comma_or_ccurly_machine);
			}
			
			if (tokenizer->token == t_comma)
			{
				read_token(tokenizer, numeric_or_ccurly_machine);
			}
			else
			{
				max = min;
			}
			
			if (false
				|| tokenizer->token == t_octal_literal
				|| tokenizer->token == t_decimal_literal
				|| tokenizer->token == t_hexadecimal_literal)
			{
				set_limit(&max);
				read_token(tokenizer, ccurly_machine);
			}
			
			if (!min.has && !max.has)
			{
				TODO;
				exit(1);
			}
			
			if (min.has) { dpv(min.value); }
			if (max.has) { dpv(max.value); }
			
			struct regex* start = new_regex();
			
			struct regex* moving = start;
			
			unsigned i = 0;
			
			if (min.has)
			{
				for (; i < min.value; i++)
				{
					struct clone_nfa_bundle clone = regex_clone_nfa(original.nfa.start, original.nfa.end);
					
					regex_add_lambda_transition(moving, clone.start);
					
					moving = clone.end;
				}
			}
			
			struct regex* end = new_regex();
			
			regex_add_lambda_transition(moving, end);
			
			if (max.has)
			{
				for (; i < max.value; i++)
				{
					struct clone_nfa_bundle clone = regex_clone_nfa(original.nfa.start, original.nfa.end);
					
					regex_add_lambda_transition(moving, clone.start);
					
					moving = clone.end;
					
					regex_add_lambda_transition(moving, end);
				}
			}
			else
			{
				struct clone_nfa_bundle clone = regex_clone_nfa(original.nfa.start, original.nfa.end);
				
				regex_add_lambda_transition(moving, clone.start);
				
				regex_add_lambda_transition(clone.end, moving);
			}
			
			retval.is_nfa = true;
			retval.nfa.start = start;
			retval.nfa.end = end;
			
			#ifdef DOTOUT
			regex_dotout(retval.nfa.start, __PRETTY_FUNCTION__);
			#endif
			
			read_token(tokenizer, regex_after_suffix_machine);
			
			free_regex(original.nfa.start);
			#endif
			break;
		}
		
		default:
			break;
	}
	
	EXIT;
	return retval;
}
















