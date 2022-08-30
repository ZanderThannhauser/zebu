
#include <assert.h>

#include <debug.h>

#include <set/unsignedchar/union.h>
#include <set/unsignedchar/difference.h>
#include <set/unsignedchar/free.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/charset/inside_intersect.h"

#include "1.range.h"
#include "2.intersect.h"

struct cbundle read_intersect_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	struct cbundle inner = read_range_charset(tokenizer, scope);
	
	if (tokenizer->token == t_ampersand)
	{
		#define left (inner)
		
		read_token(tokenizer, charset_inside_intersect_machine);
		
		struct cbundle right = read_range_charset(tokenizer, scope);
		
		struct cbundle retval;
		
		if (left.is_complement)
		{
			if (right.is_complement)
			{
				retval = (struct cbundle) {
					.is_complement = true,
					.charset = unsignedcharset_union(left.charset, right.charset),
				};
			}
			else
			{
				TODO;
			}
		}
		else
		{
			if (right.is_complement)
			{
				retval = (struct cbundle) {
					.is_complement = false,
					.charset = unsignedcharset_difference(left.charset, right.charset),
				};
			}
			else
			{
				TODO;
			}
		}
		
		free_unsignedcharset(left.charset);
		free_unsignedcharset(right.charset);
		
		#undef left
		
		EXIT;
		return retval;
	}
	else
	{
		EXIT;
		return inner;
	}
}






