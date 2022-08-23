
#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/charset/root.h"

#include "charset/struct.h"
#include "charset/new.h"
#include "charset/free.h"

#include "union.h"
#include "complement.h"

struct charset* read_complement_charset(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	struct charset* retval;
	
	if (tokenizer->token == t_tilda)
	{
		read_token(tokenizer, charset_root_machine);
		
		#ifdef WITH_ARENAS
		struct charset* inner = read_union_charset(arena, tokenizer, scope);
		#else
		struct charset* inner = read_union_charset(tokenizer, scope);
		#endif
		
		inner->is_complement = !inner->is_complement;
		
		retval = inner;
	}
	else
	{
		#ifdef WITH_ARENAS
		retval = read_union_charset(arena, tokenizer, scope);
		#else
		retval = read_union_charset(tokenizer, scope);
		#endif
	}
	
	EXIT;
	return retval;
}










