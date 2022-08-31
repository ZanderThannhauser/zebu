
#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/charset/root.h"

#include "3.union.h"
#include "4.complement.h"

struct cbundle read_complement_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	struct cbundle inner;
	
	if (tokenizer->token == t_tilda)
	{
		read_token(tokenizer, charset_root_machine);
		
		inner = read_union_charset(tokenizer, scope);
		
		EXIT;
		return (struct cbundle) {
			.is_complement = !inner.is_complement,
			.charset = inner.charset,
		};
	}
	else
	{
		inner = read_union_charset(tokenizer, scope);
		EXIT;
		return inner;
	}
}


















