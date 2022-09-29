
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <assert.h>

#include <debug.h>

#include <enums/error.h>

#include <gegex/new.h>
#include <gegex/clone.h>
#include <gegex/add_lambda_transition.h>
#include <gegex/dotout.h>
#include <gegex/free.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/token_names.h"
#include "../tokenizer/read_token.h"

#include "0.highest.h"
#include "1.suffixes.h"

struct gbundle read_suffixes_production(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	struct gbundle retval = read_highest_production(tokenizer, scope, lex);
	
	switch (tokenizer->token)
	{
		case t_plus:
		{
			gegex_add_lambda_transition(retval.accepts, retval.start);
			
			#ifdef DOTOUT
			gegex_dotout(retval.start, retval.accepts, __PRETTY_FUNCTION__);
			#endif
			
			read_token(tokenizer);
			break;
		}
		
		case t_asterisk:
		{
			gegex_add_lambda_transition(retval.accepts, retval.start);
			gegex_add_lambda_transition(retval.start, retval.accepts);
			
			#ifdef DOTOUT
			gegex_dotout(retval.start, retval.accepts, __PRETTY_FUNCTION__);
			#endif
			
			read_token(tokenizer);
			break;
		}
		
		case t_qmark:
		{
			gegex_add_lambda_transition(retval.start, retval.accepts);
			
			#ifdef DOTOUT
			gegex_dotout(retval.start, retval.accepts, __PRETTY_FUNCTION__);
			#endif
			
			read_token(tokenizer);
			break;
		}
		
		case t_ocurly:
		{
			struct gbundle original = retval;
			
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
					fprintf(stderr, "zebu: error when reading grammar-rule: strtoul('%s'): %m\n", start);
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
			
			struct gegex* start = new_gegex();
			
			struct gegex* moving = start;
			
			unsigned i = 0;
			
			if (min.has)
			{
				for (; i < min.value; i++)
				{
					struct gbundle clone = gegex_clone2(original);
					
					gegex_add_lambda_transition(moving, clone.start);
					
					moving = clone.accepts;
				}
			}
			
			struct gegex* accepts = new_gegex();
			
			gegex_add_lambda_transition(moving, accepts);
			
			if (max.has)
			{
				for (; i < max.value; i++)
				{
					struct gbundle clone = gegex_clone2(original);
					
					gegex_add_lambda_transition(moving, clone.start);
					
					moving = clone.accepts;
					
					gegex_add_lambda_transition(moving, accepts);
				}
			}
			else
			{
				struct gbundle clone = gegex_clone2(original);
				
				gegex_add_lambda_transition(moving, clone.start);
				
				gegex_add_lambda_transition(clone.accepts, moving);
			}
			
			#ifdef DOTOUT
			gegex_dotout(start, accepts, __PRETTY_FUNCTION__);
			#endif
			
			retval = (struct gbundle) {start, accepts};
			
			free_gegex(original.start);
			break;
		}
		
		default:
			break;
	}
	
	EXIT;
	return retval;
}


















