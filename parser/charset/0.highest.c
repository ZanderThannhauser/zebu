
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <enums/error.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/token_names.h"

#include "../scope/lookup/charset.h"

#include "root.h"
#include "0.highest.h"

charset_t read_highest_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	charset_t retval = {};
	ENTER;
	
	switch (tokenizer->token)
	{
		case t_character_literal:
		{
			unsigned char first = *tokenizer->tokenchars.chars;
			
			dpvc(first);
			
			retval[first >> 4] |= 1 << (first & 0xF);
			
			break;
		}
		
		case t_octal_literal:
		{
			errno = 0;
			const char* start = (void*) tokenizer->tokenchars.chars;
			unsigned long int value = strtoul(start, NULL, 8);
			
			if (errno)
			{
				fprintf(stderr, "zebu: error when reading character-set: strtoul('%s'): %s\n", start, strerror(errno));
				exit(e_syntax_error);
			}
			else if (value >= 256)
			{
				fprintf(stderr, "zebu: error when reading character-set: literal '0%lo' must be bewteen 0 and 255\n", value);
				exit(e_syntax_error);
			}
			
			retval[value >> 4] |= 1 << (value & 0xF);
			break;
		}
		
		case t_decimal_literal:
		{
			errno = 0;
			const char* start = (void*) tokenizer->tokenchars.chars;
			unsigned long int value = strtoul(start, NULL, 10);
			
			if (errno)
			{
				fprintf(stderr, "zebu: error when reading character-set: strtoul('%s'): %s\n", start, strerror(errno));
				exit(e_syntax_error);
			}
			else if (value >= 256)
			{
				fprintf(stderr, "zebu: error when reading character-set: literal '%lu' must be bewteen 0 and 255\n", value);
				exit(e_syntax_error);
			}
			
			retval[value >> 4] |= 1 << (value & 0xF);
			break;
		}
		
		case t_hexadecimal_literal:
		{
			errno = 0;
			const char* start = (void*) tokenizer->tokenchars.chars;
			unsigned long int value = strtoul(start, NULL, 16);
			
			if (errno)
			{
				fprintf(stderr, "zebu: error when reading character-set: strtoul('%s'): %s\n", start, strerror(errno));
				exit(e_syntax_error);
			}
			else if (value >= 256)
			{
				fprintf(stderr, "zebu: error when reading character-set: literal '0x%lx' must be bewteen 0 and 255\n", value);
				exit(e_syntax_error);
			}
			
			retval[value >> 4] |= 1 << (value & 0xF);
			break;
		}
		
		case t_identifier:
		{
			retval = scope_lookup_charset(scope, (void*) tokenizer->tokenchars.chars);
			break;
		}
		
		case t_oparen:
		{
			read_token(tokenizer);
			
			retval = read_root_charset(tokenizer, scope);
			
			if (tokenizer->token != t_cparen)
			{
				fprintf(stderr, "zebu: encountered syntax error on line %u: "
					"unexpected '%s', expecting '%s'!\n",
					tokenizer->line,
					token_names[tokenizer->token],
					token_names[t_cparen]);
				exit(e_syntax_error);
			}
			
			break;
		}
		
		default:
		{
			assert(token_names[tokenizer->token]);
			
			assert(token_names[t_oparen]);
			assert(token_names[t_identifier]);
			assert(token_names[t_octal_literal]);
			assert(token_names[t_decimal_literal]);
			assert(token_names[t_character_literal]);
			assert(token_names[t_hexadecimal_literal]);
			
			fprintf(stderr, "zebu: error while reading character set: "
				"unexpected '%s' token on line %u, expecting '%s', '%s', '%s', '%s', "
				"'%s', '%s'!\n",
				token_names[tokenizer->token],
				tokenizer->line,
				token_names[t_oparen],
				token_names[t_identifier],
				token_names[t_octal_literal],
				token_names[t_decimal_literal],
				token_names[t_character_literal],
				token_names[t_hexadecimal_literal]);
			exit(e_syntax_error);
			break;
		}
	}
	
	read_token(tokenizer);
	
	EXIT;
	return retval;
}










