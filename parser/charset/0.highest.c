
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/charset/after_highest.h"
#include "../tokenizer/machines/charset/root.h"

#include "../scope/lookup/charset.h"

#include "root.h"
#include "0.highest.h"

charset_t read_highest_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	switch (tokenizer->token)
	{
		case t_character_literal:
		{
			unsigned char first = *tokenizer->tokenchars.chars;
			
			dpvc(first);
			
			charset_t charset = {};
			
			charset[first >> 4] |= 1 << (first & 0xF);
			
			read_token(tokenizer, charset_after_highest_machine);
			
			EXIT;
			return charset;
		}
		
		case t_identifier:
		{
			charset_t inner = scope_lookup_charset(scope, (void*) tokenizer->tokenchars.chars);
			
			read_token(tokenizer, charset_after_highest_machine);
			
			EXIT;
			return inner;
		}
		
		case t_oparen:
		{
			read_token(tokenizer, charset_root_machine);
			
			charset_t retval = read_root_charset(tokenizer, scope);
			
			if (tokenizer->token != t_cparen)
			{
				TODO;
				exit(1);
			}
			
			read_token(tokenizer, charset_after_highest_machine);
			
			EXIT;
			return retval;
		}
		
		default:
			TODO;
			break;
	}
}










