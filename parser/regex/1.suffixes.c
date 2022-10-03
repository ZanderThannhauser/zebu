
#include <string.h>
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
#include "../tokenizer/token_names.h"

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
			if (!retval.accepts)
			{
				retval = regex_dfa_to_nfa(retval.start);
			}
			
			regex_add_lambda_transition(retval.start, retval.accepts);
			
			#ifdef DOTOUT
			regex_dotout(retval.start, __PRETTY_FUNCTION__);
			#endif
			
			read_token(tokenizer);
			break;
		}
		
		case t_asterisk:
		{
			// convert into nfa:
			if (!retval.accepts)
			{
				retval = regex_dfa_to_nfa(retval.start);
			}
			
			regex_add_lambda_transition(retval.start, retval.accepts);
			
			regex_add_lambda_transition(retval.accepts, retval.start);
			
			struct regex* new_accepts = new_regex();
			regex_add_lambda_transition(retval.accepts, new_accepts);
			retval.accepts = new_accepts;
			
			#ifdef DOTOUT
			regex_dotout(retval.start, __PRETTY_FUNCTION__);
			#endif
			
			read_token(tokenizer);
			break;
		}
		
		case t_plus:
		{
			// convert into nfa:
			if (!retval.accepts)
			{
				retval = regex_dfa_to_nfa(retval.start);
			}
			
			regex_add_lambda_transition(retval.accepts, retval.start);
			
			struct regex* new_accepts = new_regex();
			regex_add_lambda_transition(retval.accepts, new_accepts);
			retval.accepts = new_accepts;
			
			#ifdef DOTOUT
			regex_dotout(retval.start, __PRETTY_FUNCTION__);
			#endif
			
			read_token(tokenizer);
			break;
		}
		
		case t_ocurly:
		{
			struct rbundle original;
			
			// convert into nfa:
			if (retval.accepts)
				original = retval;
			else
				original = regex_dfa_to_nfa(retval.start);
			
			struct limit {
				bool has;
				unsigned value;
			} min = {}, max = {};
			
			void set_limit(struct limit* l)
			{
				int base;
				
				switch (tokenizer->token)
				{
					case t_octal_literal: base = 8; break;
					case t_decimal_literal: base = 10; break;
					case t_hexadecimal_literal: base = 16; break;
					default: TODO; break;
				}
				
				errno = 0;
				const char* start = (void*) tokenizer->tokenchars.chars;
				unsigned long int value = strtoul(start, NULL, base);
				
				if (errno)
				{
					fprintf(stderr, "zebu: error when reading grammar-rule: strtoul('%s'): %s\n", start, strerror(errno));
					exit(e_syntax_error);
				}
				
				l->has = true;
				l->value = value;
			}
			
			read_token(tokenizer);
			
			if (false
				|| tokenizer->token == t_octal_literal
				|| tokenizer->token == t_decimal_literal
				|| tokenizer->token == t_hexadecimal_literal)
			{
				set_limit(&min);
				read_token(tokenizer);
			}
			
			if (tokenizer->token == t_comma)
				read_token(tokenizer);
			else
				max = min;
			
			if (false
				|| tokenizer->token == t_octal_literal
				|| tokenizer->token == t_decimal_literal
				|| tokenizer->token == t_hexadecimal_literal)
			{
				set_limit(&max);
				read_token(tokenizer);
			}
			
			if (tokenizer->token != t_ccurly)
			{
				fprintf(stderr, "zebu: encountered syntax error on line %u: "
					"unexpected '%s', expecting '%s'!\n",
					tokenizer->line,
					token_names[tokenizer->token],
					token_names[t_ccurly]);
				exit(e_syntax_error);
			}
			
			read_token(tokenizer);
			
			if (min.has) { dpv(min.value); }
			if (max.has) { dpv(max.value); }
			
			struct regex* start = new_regex();
			
			struct regex* moving = start;
			
			unsigned i = 0;
			
			if (min.has)
			{
				for (; i < min.value; i++)
				{
					struct rbundle clone = regex_clone2(original);
					
					regex_add_lambda_transition(moving, clone.start);
					
					moving = clone.accepts;
				}
			}
			
			struct regex* accepts = new_regex();
			
			regex_add_lambda_transition(moving, accepts);
			
			if (max.has)
			{
				for (; i < max.value; i++)
				{
					struct rbundle clone = regex_clone2(original);
					
					regex_add_lambda_transition(moving, clone.start);
					
					moving = clone.accepts;
					
					regex_add_lambda_transition(moving, accepts);
				}
			}
			else
			{
				struct rbundle clone = regex_clone2(original);
				
				regex_add_lambda_transition(moving, clone.start);
				
				regex_add_lambda_transition(clone.accepts, moving);
			}
			
			retval.start = start;
			retval.accepts = accepts;
			
			#ifdef DOTOUT
			regex_dotout(retval.start, __PRETTY_FUNCTION__);
			#endif
			
			free_regex(original.start);
			break;
		}
		
		default:
			break;
	}
	
	EXIT;
	return retval;
}
















