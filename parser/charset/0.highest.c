
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/charset/after_highest.h"
#include "../tokenizer/machines/charset/root.h"

/*#include "../scope/lookup/charset.h"*/

#include "charset/new.h"
/*#include "charset/clone.h"*/

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
			TODO;
			#if 0
			struct charset* copyme = scope_lookup_charset(scope, tokenizer->tokenchars.chars);
			
			#ifdef WITH_ARENAS
			retval = clone_charset(arena, copyme);
			#else
			retval = clone_charset(copyme);
			#endif
			#endif
			break;
		}
		
		case t_oparen:
		{
			TODO;
			#if 0
			read_token(tokenizer, charset_root_machine);
			
			#ifdef WITH_ARENAS
			retval = read_root_charset(arena, tokenizer, scope);
			#else
			retval = read_root_charset(tokenizer, scope);
			#endif
			
			if (tokenizer->token != t_cparen)
			{
				TODO;
				exit(1);
			}
			#endif
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










