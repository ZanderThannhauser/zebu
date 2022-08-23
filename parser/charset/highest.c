
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/charset/after_highest.h"
#include "../tokenizer/machines/charset/root.h"

#include "../scope/lookup/charset.h"

#include "charset/new.h"
#include "charset/clone.h"

#include "root.h"
#include "highest.h"

struct charset* read_highest_charset(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
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
			
			#ifdef WITH_ARENAS
			retval = new_charset(arena, &first, 1, false);
			#else
			retval = new_charset(&first, 1, false);
			#endif
			break;
		}
		
		case t_identifier:
		{
			struct charset* copyme = scope_lookup_charset(scope, tokenizer->tokenchars.chars);
			
			#ifdef WITH_ARENAS
			retval = clone_charset(arena, copyme);
			#else
			retval = clone_charset(copyme);
			#endif
			break;
		}
		
		case t_oparen:
		{
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











