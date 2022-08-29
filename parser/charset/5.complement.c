
#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/charset/root.h"

#include "charset/struct.h"
/*#include "charset/new.h"*/
/*#include "charset/free.h"*/

#include "4.union.h"
#include "5.complement.h"

struct charset* read_complement_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	struct charset* retval;
	
	if (tokenizer->token == t_tilda)
	{
		read_token(tokenizer, charset_root_machine);
		
		struct charset* inner = read_union_charset(tokenizer, scope);
		
		inner->is_complement = !inner->is_complement;
		
		retval = inner;
	}
	else
	{
		retval = read_union_charset(tokenizer, scope);
	}
	
	EXIT;
	return retval;
}









