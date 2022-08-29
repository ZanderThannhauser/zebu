
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "read_char.h"
#include "read_token.h"

static void append(struct tokenizer* this, char c)
{
	ENTER;
	
	dpvc(c);
	
	if (this->tokenchars.n + 1 >= this->tokenchars.cap)
	{
		this->tokenchars.cap = this->tokenchars.cap * 2 ?: 1;
		
		dpv(this->tokenchars.cap);
		
		this->tokenchars.chars = realloc(this->tokenchars.chars, this->tokenchars.cap);
		
		assert(this->tokenchars.chars);
	}
	
	this->tokenchars.chars[this->tokenchars.n++] = c;
	
	EXIT;
}

enum token read_token(
	struct tokenizer* this,
	const enum tokenizer_state machine[number_of_tokenizer_states][256])
{
	ENTER;
	
	dpvc(this->c);
	
	this->tokenchars.n = 0;
	
	enum tokenizer_state state = ts_start;
	
	while (state >= ts_start)
	{
		state = machine[state][(unsigned) this->c];
		
		if (state > ts_start)
			append(this, this->c);
		else if (state == ts_start)
			this->tokenchars.n = 0;
		
		if (state >= ts_start)
			read_char(this);
	}
	
	switch (state)
	{
		case ts_error:
			TODO;
			break;
		
		case ts_EOF:
			this->token = t_EOF;
			break;
		
		case ts_directive:
			append(this, 0);
			this->token = t_directive;
			dputs("t_directive");
			break;
		
		case ts_numeric_literal:
			append(this, 0);
			this->token = t_numeric_literal;
			dputs("t_numeric_literal");
			break;
		
		case ts_start:
			TODO;
			break;
		
		case ts_skipping_comment:
			TODO;
			break;
		
		case ts_after_slash:
			TODO;
			break;
		
		case ts_after_percent:
			TODO;
			break;
		
		void escapes()
		{
			ENTER;
			
			dpvsn(this->tokenchars.chars, this->tokenchars.n);
			
			unsigned char* s = this->tokenchars.chars;
			
			unsigned char* w = s, *r = w + 1, *n = w + this->tokenchars.n - 1;
			
			while (r < n)
			{
				dpvc(*r);
				
				if (*r != '\\')
					*w++ = *r++;
				else switch (*++r)
				{
					case 'n': *w++ = '\n', r++; break;
					
					case 't': *w++ = '\t', r++; break;
					
					case '\\': *w++ = '\\', r++; break;
					
					case '\'': *w++ = '\'', r++; break;
					
					case '\"': *w++ = '\"', r++; break;
					
					default:
					{
						dpvc(*r);
						TODO;
						break;
					}
				}
			}
			
			this->tokenchars.n = w - s;
			
			dpvsn(this->tokenchars.chars, this->tokenchars.n);
			
			EXIT;
		}
		
		case ts_character_literal:
		{
			this->token = t_character_literal;
			dputs("t_character_literal");
			escapes();
			break;
		}
		
		case ts_string_literal:
		{
			this->token = t_string_literal;
			dputs("t_string_literal");
			escapes();
			break;
		}
		
		case ts_absolute_path:
		{
			// remove quotes:
			memmove(this->tokenchars.chars, this->tokenchars.chars + 1, this->tokenchars.n);
			this->tokenchars.n -= 2;
			append(this, 0);
			
			dpvs(this->tokenchars.chars);
			
			this->token = t_absolute_path;
			dputs("t_absolute_path");
			break;
		}
		
		case ts_relative_path:
		{
			TODO;
			this->token = t_relative_path;
			dputs("t_relative_path");
			break;
		}
		
		case ts_bracketed_identifier:
		{
			// remove backets:
			memmove(this->tokenchars.chars, this->tokenchars.chars + 1, this->tokenchars.n);
			this->tokenchars.n -= 2;
			append(this, 0);
			
			dpvs(this->tokenchars.chars);
			
			this->token = t_bracketed_identifier;
			dputs("t_bracketed_identifier");
			break;
		}
		
		case ts_gravemarked_identifier:
		{
			// remove gravemarks:
			memmove(this->tokenchars.chars, this->tokenchars.chars + 1, this->tokenchars.n);
			this->tokenchars.n -= 2;
			append(this, 0);
			
			dpvs(this->tokenchars.chars);
			
			this->token = t_gravemarked_identifier;
			dputs("t_gravemarked_identifier");
			break;
		}
		
		case ts_parenthesised_identifier:
		{
			// remove parenthesis:
			memmove(this->tokenchars.chars, this->tokenchars.chars + 1, this->tokenchars.n);
			this->tokenchars.n -= 2;
			append(this, 0);
			
			dpvs(this->tokenchars.chars);
			
			this->token = t_parenthesised_identifier;
			dputs("t_parenthesised_identifier");
			break;
		}
		
		case ts_identifier:
			append(this, 0);
			this->token = t_identifier;
			dputs("t_identifier");
			break;
		
		case ts_hashtag:
		{
			// remove #:
			memmove(this->tokenchars.chars, this->tokenchars.chars + 1, this->tokenchars.n);
			
			this->tokenchars.n -= 1;
			
			append(this, 0);
			
			this->token = t_hashtag;
			dputs("t_hashtag");
			break;
		}
		
		case ts_colon:
			this->token = t_colon;
			dputs("t_colon");
			break;
		
		case ts_plus:
			this->token = t_plus;
			dputs("t_plus");
			break;
		
		case ts_lthan:
			this->token = t_lthan;
			break;
		
		case ts_gthan:
			this->token = t_gthan;
			break;
		
		case ts_comma:
			this->token = t_comma;
			dputs("t_comma");
			break;
		
		case ts_emark:
			this->token = t_emark;
			dputs("t_emark");
			break;
		
		case ts_qmark:
			this->token = t_qmark;
			dputs("t_qmark");
			break;
		
		case ts_ampersand:
			this->token = t_ampersand;
			dputs("t_ampersand");
			break;
		
		case ts_oparen:
			this->token = t_oparen;
			dputs("t_oparen");
			break;
		
		case ts_tilda:
			this->token = t_tilda;
			dputs("t_tilda");
			break;
		
		case ts_dot:
			this->token = t_dot;
			dputs("t_dot");
			break;
		
		case ts_cparen:
			this->token = t_cparen;
			dputs("t_cparen");
			break;
		
		case ts_asterisk:
			this->token = t_asterisk;
			dputs("t_asterisk");
			break;
		
		case ts_osquare:
			this->token = t_osquare;
			dputs("t_osquare");
			break;
		
		case ts_csquare:
			this->token = t_csquare;
			dputs("t_csquare");
			break;
		
		case ts_equal_to:
			TODO;
			break;
		
		case ts_vertical_bar:
			this->token = t_vertical_bar;
			dputs("t_vertical_bar");
			break;
		
		case ts_semicolon:
			this->token = t_semicolon;
			dputs("t_semicolon");
			break;
		
		case ts_gravemark:
			this->token = t_gravemark;
			dputs("t_gravemark");
			break;
		
		case ts_hypen:
			this->token = t_hypen;
			dputs("t_hypen");
			break;
		
		case ts_percent:
			this->token = t_percent;
			dputs("t_percent");
			break;
		
		case ts_ocurly:
			this->token = t_ocurly;
			dputs("t_ocurly");
			break;
		
		case ts_ccurly:
			this->token = t_ccurly;
			dputs("t_ccurly");
			break;
		
		default:
			TODO;
			break;
	}
	
	EXIT;
	return this->token;
}

















