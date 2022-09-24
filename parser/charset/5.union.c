
#include <stdbool.h>

#include <assert.h>

#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/token_names.h"

#include "4.xor.h"
#include "5.union.h"

charset_t read_union_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	charset_t left = read_xor_charset(tokenizer, scope);
	
	again: switch (tokenizer->token)
	{
		case t_vbar:
		case t_comma:
			read_token(tokenizer);
		case t_oparen:
		case t_octal_literal:
		case t_decimal_literal:
		case t_character_literal:
		case t_hexadecimal_literal:
		{
			charset_t right = read_xor_charset(tokenizer, scope);
			left |= right;
			goto again;
		}
		
		case t_cparen:
		case t_csquare:
		case t_semicolon:
			break;
		
		default:
			dpvs(token_names[tokenizer->token]);
			TODO;
			break;
	}
	
	EXIT;
	return left;
}

















