
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <set/unsignedchar/new.h>
#include <set/unsignedchar/add.h>
#include <set/unsignedchar/inc.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/charset/after_highest.h"
#include "../tokenizer/machines/charset/root.h"

#include "../scope/lookup/charset.h"

#include "root.h"
#include "0.highest.h"

struct cbundle read_highest_charset(
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
			
			struct unsignedcharset* set = new_unsignedcharset();
			
			unsignedcharset_add(set, first);
			
			read_token(tokenizer, charset_after_highest_machine);
			
			EXIT;
			return (struct cbundle) {
				.is_complement = false,
				.charset = set,
			};
		}
		
		case t_identifier:
		{
			struct cbundle inner = scope_lookup_charset(scope, (void*) tokenizer->tokenchars.chars);
			
			read_token(tokenizer, charset_after_highest_machine);
			
			EXIT;
			return (struct cbundle) {
				.is_complement = inner.is_complement,
				.charset = inc_unsignedcharset(inner.charset),
			};
		}
		
		case t_oparen:
		{
			read_token(tokenizer, charset_root_machine);
			
			struct cbundle retval = read_root_charset(tokenizer, scope);
			
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










