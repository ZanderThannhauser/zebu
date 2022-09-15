
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <enums/error.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/charset/after_highest.h"
#include "../tokenizer/machines/charset/root.h"

#include "../scope/lookup/charset.h"

#include "root.h"
#include "0.highest.h"

charset_t read_highest_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	switch (tokenizer->token)
	{
		case t_character_literal:
		{
			unsigned char first = *tokenizer->tokenchars.chars;
			
			dpvc(first);
			
			charset_t charset = {};
			
			charset[first >> 4] |= 1 << (first & 0xF);
			
			read_token(tokenizer, charset_after_highest_machine);
			
			EXIT;
			return charset;
		}
		
		case t_octal_literal:
		{
			dpvs(tokenizer->tokenchars.chars);
			
			errno = 0;
			const char* start = (void*) tokenizer->tokenchars.chars;
			unsigned long int value = strtoul(start, NULL, 8);
			
			if (errno)
			{
				fprintf(stderr, "zebu: error when reading character-set: strtoul(): %m\n");
				exit(e_syntax_error);
			}
			else if (value >= 256)
			{
				fprintf(stderr, "zebu: error when reading character-set: literal '%lu' must be bewteen 0 and 255\n", value);
				exit(e_syntax_error);
			}
			
			charset_t charset = {};
			
			charset[value >> 4] |= 1 << (value & 0xF);
			
			read_token(tokenizer, charset_after_highest_machine);
			
			EXIT;
			return charset;
		}
		
		case t_decimal_literal:
		{
			dpvs(tokenizer->tokenchars.chars);
			
			errno = 0;
			const char* start = (void*) tokenizer->tokenchars.chars;
			unsigned long int value = strtoul(start, NULL, 10);
			
			if (errno)
			{
				fprintf(stderr, "zebu: error when reading character-set: strtoul(): %m\n");
				exit(e_syntax_error);
			}
			else if (value >= 256)
			{
				fprintf(stderr, "zebu: error when reading character-set: literal '%lu' must be bewteen 0 and 255\n", value);
				exit(e_syntax_error);
			}
			
			charset_t charset = {};
			
			charset[value >> 4] |= 1 << (value & 0xF);
			
			read_token(tokenizer, charset_after_highest_machine);
			
			EXIT;
			return charset;
		}
		
		case t_hexadecimal_literal:
		{
			dpvs(tokenizer->tokenchars.chars);
			
			errno = 0;
			const char* start = (void*) tokenizer->tokenchars.chars;
			unsigned long int value = strtoul(start, NULL, 16);
			
			if (errno)
			{
				fprintf(stderr, "zebu: error when reading character-set: strtoul(): %m\n");
				exit(e_syntax_error);
			}
			else if (value >= 256)
			{
				fprintf(stderr, "zebu: error when reading character-set: literal '0x%lX' must be bewteen 0 and 255\n", value);
				exit(e_syntax_error);
			}
			
			charset_t charset = {};
			
			charset[value >> 4] |= 1 << (value & 0xF);
			
			read_token(tokenizer, charset_after_highest_machine);
			
			EXIT;
			return charset;
		}
		
		case t_identifier:
		{
			charset_t inner = scope_lookup_charset(scope, (void*) tokenizer->tokenchars.chars);
			
			read_token(tokenizer, charset_after_highest_machine);
			
			EXIT;
			return inner;
		}
		
		case t_oparen:
		{
			read_token(tokenizer, charset_root_machine);
			
			charset_t retval = read_root_charset(tokenizer, scope);
			
			if (tokenizer->token != t_cparen)
			{
				TODO;
				exit(1);
			}
			
			read_token(tokenizer, charset_after_highest_machine);
			
			EXIT;
			return retval;
		}
		
		default:
			TODO;
			break;
	}
}










