
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/charset/after_highest.h"
#include "../tokenizer/machines/charset/root.h"

#include "../scope/lookup/charset.h"

#include <charset/new.h>
#include <charset/clone.h>

#include "root.h"
#include "0.highest.h"

struct charset* read_highest_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	struct charset* retval;
	ENTER;
	
	switch (tokenizer->token)
	{
		case t_character_literal:
		{
			unsigned char first = *tokenizer->tokenchars.chars;
			
			dpvc(first);
			
			retval = new_charset(&first, 1, false);
			
			break;
		}
		
		case t_identifier:
		{
			struct charset* copyme = scope_lookup_charset(scope, (void*) tokenizer->tokenchars.chars);
			
			retval = clone_charset(copyme);
			break;
		}
		
		case t_oparen:
		{
			read_token(tokenizer, charset_root_machine);
			
			retval = read_root_charset(tokenizer, scope);
			
			if (tokenizer->token != t_cparen)
			{
				TODO;
				exit(1);
			}
			
			break;
		}
		
		default:
			TODO;
			break;
	}
	
	read_token(tokenizer, charset_after_highest_machine);
	
	EXIT;
	return retval;
}










