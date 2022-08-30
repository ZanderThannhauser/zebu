
#include <assert.h>

#include <stdlib.h>

#include <debug.h>

#include <macros/min.h>
#include <macros/max.h>

#include <set/unsignedchar/new.h>
#include <set/unsignedchar/add.h>
#include <set/unsignedchar/min.h>
#include <set/unsignedchar/max.h>
#include <set/unsignedchar/free.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/charset/inside_range.h"

#include "0.highest.h"
#include "1.range.h"

struct cbundle read_range_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	struct cbundle inner = read_highest_charset(tokenizer, scope);
	
	if (tokenizer->token == t_hypen)
	{
		#define left (inner)
		
		read_token(tokenizer, charset_inside_range_machine);
		
		struct cbundle right = read_highest_charset(tokenizer, scope);
		
		if (left.is_complement || right.is_complement)
		{
			TODO;
			exit(e_bad_input_file);
		}
		
		unsigned char l = unsignedcharset_min(left.charset);
		unsigned char r = unsignedcharset_max(right.charset);
		
		dpv(l);
		dpv(r);
		
		unsigned char min = min(l, r), max = max(l, r);
		
		struct unsignedcharset* set = new_unsignedcharset();
		
		for (unsigned i = min; i <= max; i++)
			unsignedcharset_add(set, i);
		
		free_unsignedcharset(left.charset), free_unsignedcharset(right.charset);
		
		#undef left
		EXIT;
		return (struct cbundle) {
			.is_complement = false,
			.charset = set,
		};
	}
	else
	{
		EXIT;
		return inner;
	}
}








