
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct format_flags* new_format_flags(
	unsigned char* data, unsigned len)
{
	ENTER
	
	dpvsn(data, len);
	
	if (len)
	{
		if (*data != '%')
		{
			TODO;
			exit(1);
		}
		
		data++, len--;
	}
	
	int max_field_width = -1;
	
	if (len && memchr("0123456789", *data, 10))
	{
		max_field_width = 0;
		do max_field_width = max_field_width * 10 + *data - '0';
		while (len && memchr("0123456789", *data, 10));
		dpv(max_field_width);
	}
	
	enum length_modifier length_modifier = lm_int;
	const char* length_modifier_text = "";
	
	if (len) switch (*data)
	{
		case 'h':
			data++, len--;
			if (len && *data == 'h')
			{
				data++, len--;
				length_modifier_text = "hh";
				length_modifier = lm_char;
			}
			else
			{
				length_modifier_text = "h";
				length_modifier = lm_short;
			}
		break;
		
		case 'l':
			data++, len--;
			if (len && *data == 'l')
			{
				data++, len--;
				length_modifier_text = "ll";
				length_modifier = lm_long_long;
			}
			else
			{
				length_modifier_text = "l";
				length_modifier = lm_long;
			}
		break;
		
		case 'L':
			data++, len--;
			length_modifier_text = "L";
			length_modifier = lm_long_double;
			break;
		
		case 'j':
			data++, len--;
			length_modifier_text = "j";
			length_modifier = lm_intmax;
			break;
		
		case 'z':
			data++, len--;
			length_modifier_text = "z";
			length_modifier = lm_size;
			break;
		
		case 't':
			data++, len--;
			length_modifier_text = "t";
			length_modifier = lm_ptrdiff;
			break;
		
		default:
			break;
	}
	
	if (!len)
	{
		TODO;
		exit(1);
	}
	
	const char* ctype;
	
	char conversion = *data;
	
	switch (conversion)
	{
		case 'd':
		case 'i': switch (length_modifier)
		{
			case lm_char: ctype = "signed char"; break;
			case lm_short: ctype = "signed short"; break;
			case lm_int: ctype = "signed int"; break;
			case lm_long: ctype = "signed long"; break;
			case lm_long_long: ctype = "signed long long"; break;
			default: TODO; break;
		}
		break;
		
		case 'o':
		case 'u':
		case 'x':
		case 'X': switch (length_modifier)
		{
			case lm_char: ctype = "unsigned char"; break;
			case lm_short: ctype = "unsigned short"; break;
			case lm_int: ctype = "unsigned int"; break;
			case lm_long: ctype = "unsigned long"; break;
			case lm_long_long: ctype = "unsigned long long"; break;
			default: TODO; break;
		}
		break;
		
		case 'e':
		case 'E':
		case 'g':
		case 'G':
		case 'a':
		case 'A':
		case 'f':
		case 'F': switch (length_modifier)
		{
			case lm_int: ctype = "float"; break;
			case lm_long: ctype = "double"; break;
			case lm_long_double: ctype = "long double"; break;
			default: TODO; break;
		}
		break;
		
		case 'c': switch (length_modifier)
		{
			case lm_int: ctype = "char"; break;
			case lm_long: ctype = "wchar_t"; break;
			default: TODO; break;
		}
		break;
		
		case 's': switch (length_modifier)
		{
			case lm_int: ctype = "char*"; break;
			case lm_long: ctype = "wchar_t*"; break;
			default: TODO; break;
		}
		break;
		
		case 'p': ctype = "void*"; break;
		
		default: TODO; break;
	}
	
	dpv(max_field_width);
	dpvc(conversion);
	dpvs(ctype);
	
	struct format_flags* new = smalloc(sizeof(*new));
	
	new->max_field_width = max_field_width;
	new->length_modifier_text = length_modifier_text;
	new->length_modifier = length_modifier;
	new->conversion = conversion;
	new->ctype = ctype;
	
	new->refcount = 1;
	
	EXIT;
	return new;
}














