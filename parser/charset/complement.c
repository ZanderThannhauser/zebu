
#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/charset/root.h"

#include "charset/struct.h"
#include "charset/new.h"
#include "charset/inc.h"
#include "charset/free.h"

#include "highest.h"
#include "complement.h"

struct charset* read_complement_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	bool take_complement = false;
	
	if (tokenizer->token == t_tilda)
	{
		take_complement = true;
		read_token(tokenizer, charset_root_machine);
	}
	
	struct charset* retval;
	struct charset* inner = read_highest_charset(tokenizer, scope);
	
	if (take_complement)
	{
		retval = new_charset(
			inner->chars, inner->len,
			/* is_complement: */ true);
	}
	else
	{
		retval = inc_charset(inner);
	}
	
	free_charset(inner);
	
	EXIT;
	return retval;
}









