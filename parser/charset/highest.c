
#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/charset/after_highest.h"

#include "../scope/lookup/charset.h"

#include "charset/new.h"
#include "highest.h"

struct charset* read_highest_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	struct charset* retval;
	ENTER;
	
	switch (tokenizer->token)
	{
		case t_character_literal:
			retval = new_charset(
				/* src: */ tokenizer->tokenchars.chars + 1,
				/* len: */ 1,
				/* is_complement: */ false);
			break;
		
		case t_identifier:
			retval = scope_lookup_charset(scope, tokenizer->tokenchars.chars);
			break;
		
		case t_oparen:
			TODO;
			break;
		
		default:
			TODO;
			break;
	}
	
	read_token(tokenizer, charset_after_highest_machine);
	
	EXIT;
	return retval;
}











