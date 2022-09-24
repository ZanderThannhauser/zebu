
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

#include <debug.h>

#include <enums/error.h>

#include <parser/tokenizer/struct.h>

#include <regex/from_literal.h>
#include <regex/dotout.h>

#include "numeric_literal.h"

struct rbundle read_numeric_literal_token_expression(
	struct tokenizer* tokenizer)
{
	ENTER;
	
	int base;
	switch (tokenizer->token)
	{
		case t_octal_literal: base = 8; break;
		
		case t_decimal_literal: base = 10; break;
		
		case t_hexadecimal_literal: base = 16; break;
		
		default:
			TODO;
			break;
	}
	
	dpvs(tokenizer->tokenchars.chars);
	
	errno = 0;
	const char* tokenizer_start = (void*) tokenizer->tokenchars.chars;
	unsigned long int value = strtoul(tokenizer_start, NULL, base);
	
	if (errno)
	{
		fprintf(stderr, "zebu: error when reading regular-expression: strtoul('%s'): %m\n", tokenizer_start);
		exit(e_syntax_error);
	}
	else if (value >= 256)
	{
		fprintf(stderr, "zebu: error when reading regular-expression: literal '%lu' must be bewteen 0 and 255\n", value);
		exit(e_syntax_error);
	}
	
	unsigned char code = value;
	
	struct regex* dfa = regex_from_literal(&code, 1);
	
	#ifdef DOTOUT
	regex_dotout(dfa, __PRETTY_FUNCTION__);
	#endif
	
	EXIT;
	return (struct rbundle) {
		.is_nfa = false,
		.dfa = dfa,
	};
}

















